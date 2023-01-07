/*
 * Copyright (C) 2023 Jan Hamal Dvořák <mordae@anilinux.org>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "task.h"

#include <pico/stdlib.h>
#include <hardware/sync.h>

#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <setjmp.h>
#include <stdio.h>


enum {
	R4 = 0,
	R5,
	R6,
	R7,
	R8,
	R9,
	R10,
	FP,
	SP,
	PC,
};


struct task {
	/* Saved registers, including stack pointer. */
	jmp_buf regs;

	/* NULL or memory to `free()` after task returns. */
	void *memory;

	/* Task priority. High priority tasks run first. */
	int pri;

	/* '\0'-terminated task name. */
	char name[9];

	/* Timestamp when was the task resumed the last time. */
	uint32_t resumed_at;

	/* Task is ready and can be resumed. */
	bool ready : 1;

	/* Task is waiting for an event. Do not resume. */
	bool blocked : 1;
};


enum task_status {
	TASK_SAVE = 0,
	TASK_YIELD,
	TASK_RETURN,
};


task_t task_running[NUM_CORES] = {0};
task_t task_avail[NUM_CORES][MAX_TASKS] = {0};

task_stats_t task_stats[NUM_CORES][MAX_TASKS] = {0};


/* Saved scheduler context for respective cores. */
static jmp_buf task_return[NUM_CORES];


/*
 * Starts task in the R4 register and converts its return
 * into longjmp back into the scheduler.
 */
static void task_sentinel(void)
{
	void (*fn)(void);
	asm volatile ("mov %0, r4" : "=r"(fn));
	fn();
	longjmp(task_return[get_core_num()], TASK_RETURN);
}


inline static bool task_runnable(task_t task)
{
	if (!task)
		return false;

	if (!task->ready)
		return false;

	if (task->blocked)
		return false;

	return true;
}


static int task_select(void)
{
	static size_t offset[NUM_CORES] = {};

	int best_task_id = -1;
	int min_pri = INT_MIN;

	for (size_t i = 0; i < MAX_TASKS; i++) {
		size_t tid = (offset[get_core_num()] + i) % MAX_TASKS;
		task_t task = task_avail[get_core_num()][tid];

		if (!task_runnable(task))
			continue;

		if (task->pri > min_pri) {
			min_pri = task->pri;
			best_task_id = tid;
		}
	}

	offset[get_core_num()] += 1;

	return best_task_id;
}


void task_init(void)
{
	for (int i = 0; i < NUM_CORES; i++) {
		task_running[i] = NULL;
		memset(task_avail[i], 0, sizeof(task_avail[i]));
	}
}


bool task_run(void)
{
	int task_no = task_select();
	int core = get_core_num();

	if (task_no < 0)
		return false;

	task_t task = task_avail[core][task_no];

	enum task_status status;
	status = setjmp(task_return[core]);

	if (TASK_SAVE == status) {
		task_stats[core][task_no].resumed++;
		task_avail[core][task_no]->resumed_at = time_us_32();
		task_running[core] = task;
		longjmp(task->regs, (int)task);
	}

	if (TASK_YIELD == status) {
		uint32_t since = task_avail[core][task_no]->resumed_at;
		task_stats[core][task_no].total_us += time_us_32() - since;
		task_running[core] = NULL;
		return true;
	}

	if (TASK_RETURN == status) {
		task_running[core] = NULL;
		task_avail[core][task_no] = NULL;

		if (task->memory)
			free(task->memory);

		return true;
	}

	panic("invalid setjmp status (%i)", status);
}



__noreturn void task_run_loop(void)
{
	while (true) {
		/* Work until we run out of ready tasks. */
		while (task_run())
			/* loop */;

		/*
		 * Sleep until an interrupt or event happens.
		 *
		 * If an event arrived since the last WFE, it does not sleep.
		 * That way the potential race condition is mitigated.
		 */
		__wfe();

		/* Unblock tasks waiting for an event. */
		task_unblock();
	}
}


void task_unblock(void)
{
	int core = get_core_num();

	for (int i = 0; i < MAX_TASKS; i++)
		task_avail[core][i]->blocked = false;
}


task_t task_create(void (*fn)(void), void *stack, size_t size)
{
	return task_create_on_core(get_core_num(), fn, stack, size);
}


task_t task_create_on_core(int core, void (*fn)(void), void *stack, size_t size)
{
	assert (size >= 128);

	void *memory = NULL;

	if (NULL == stack) {
		stack = malloc(size);
		if (NULL == stack) {
			panic("task_create: failed to allocate stack (size=%u)", size);
		}

		memory = stack;
	}

	struct task *task = stack + size - sizeof(*task);
	memset(task, 0, sizeof(*task));

	task->memory = memory;
	task->regs[SP] = (unsigned)task;
	task->regs[PC] = (unsigned)task_sentinel;
	task->regs[R4] = (unsigned)fn;

	for (int i = 0; i < MAX_TASKS; i++) {
		if (!task_avail[core][i]) {
			task_avail[core][i] = task;
			return task;
		}
	}

	panic("Too many tasks on core %u (MAX_TASKS=%u)", core, MAX_TASKS);
}


void task_yield(void)
{
	int core = get_core_num();

	if (NULL == task_running[core])
		panic("task_yield called from outside of a task");

	if (0 == setjmp(task_running[core]->regs)) {
		longjmp(task_return[core], TASK_YIELD);
	}
}


void task_yield_until_event(void)
{
	int core = get_core_num();

	if (NULL == task_running[core])
		panic("task_yield_until_event called from outside of a task");

	task_running[core]->blocked = true;
	task_yield();
}


void task_yield_until_ready(void)
{
	int core = get_core_num();

	if (NULL == task_running[core])
		panic("task_yield_until_ready called from outside of a task");

	task_running[core]->ready = false;
	task_yield();
}


void task_set_ready(task_t task)
{
	task->ready = true;
}


void task_set_priority(task_t task, int pri)
{
	task->pri = pri;
}


static int64_t task_ready_alarm(alarm_id_t id, void *arg)
{
	task_t task = arg;
	task_set_ready(task);
	return 0;
}


void task_sleep_us(uint64_t us)
{
	int core = get_core_num();

	if (NULL == task_running[core])
		panic("task_sleep_us called from outside of a task");

	task_t task = task_running[core];
	(void)add_alarm_in_us(us, task_ready_alarm, task, true);
	task_yield_until_ready();
}


void task_sleep_ms(uint64_t ms)
{
	int core = get_core_num();

	if (NULL == task_running[core])
		panic("task_sleep_ms called from outside of a task");

	task_t task = task_running[core];
	(void)add_alarm_in_us(1000 * ms, task_ready_alarm, task, true);
	task_yield_until_ready();
}


void task_yield_until(uint64_t us)
{
	int core = get_core_num();

	if (NULL == task_running[core])
		panic("task_yield_until called from outside of a task");

	task_t task = task_running[core];
	(void)add_alarm_at(us, task_ready_alarm, task, true);
	task_yield_until_ready();
}


int task_get_priority(task_t task)
{
	return task->pri;
}


void task_set_name(task_t task, const char *name)
{
	strncpy(task->name, name, sizeof(task->name));
	task->name[sizeof(task->name) - 1] = '\0';
}


void task_get_name(task_t task, char name[9])
{
	strcpy(name, task->name);
}


void task_stats_report_reset(unsigned core)
{
	uint32_t total_us = 0;

	for (int i = 0; i < MAX_TASKS; i++)
		total_us += task_stats[core][i].total_us;

	if (!total_us)
		total_us = 1;

	for (int i = 0; i < MAX_TASKS; i++) {
		if (NULL == task_avail[core][i])
			continue;

		unsigned percent = 100 * task_stats[core][i].total_us / total_us;

		printf("task: %2i (%4i) [%-8s] %5ux = %7u us = %3u%%\n",
		       i, task_avail[core][i]->pri, task_avail[core][i]->name,
		       task_stats[core][i].resumed,
		       task_stats[core][i].total_us,
		       percent);
	}

	task_stats_reset(core);
}


void task_stats_reset(unsigned core)
{
	memset(task_stats[core], 0, sizeof(task_stats[core]));
}


/****************************************************************************
 * Compatibility layer to use tasks with blocking SDK functions.            *
 ****************************************************************************/

void task_lock_spin_unlock_with_notify(volatile unsigned long *lock, unsigned long save)
{
	spin_unlock(lock, save);
	__sev();
}

void task_lock_spin_unlock_with_wait(volatile unsigned long *lock, unsigned long save)
{
	spin_unlock(lock, save);

	if (task_running[get_core_num()]) {
		task_yield_until_event();
	} else {
		__wfe();
	}
}

int task_lock_spin_unlock_with_timeout(volatile unsigned long *lock, unsigned long save, unsigned long long time)
{
	spin_unlock(lock, save);

	if (task_running[get_core_num()]) {
		task_yield_until_event();
		return time_us_64() >= time;
	} else {
		return best_effort_wfe_or_timeout(time);
	}
}

void task_sync_yield_until_before(unsigned long long time)
{
	if (task_running[get_core_num()]) {
		task_yield_until(time);
	}
}
