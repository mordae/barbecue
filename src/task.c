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

#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <setjmp.h>
#include <stdio.h>

#if !defined(__noreturn)
# define __noreturn  __attribute__((noreturn))
#endif


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
	jmp_buf regs;
	void *memory;
	int pri;
	char name[9];
	bool ready : 1;
};


enum task_status {
	TASK_SAVE = 0,
	TASK_YIELD,
	TASK_RETURN,
};


task_t task_running[NUM_CORES];
task_t task_avail[NUM_CORES][MAX_TASKS];


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


bool task_run(void)
{
	int pri = INT_MIN;

	for (int i = 0; i < MAX_TASKS; i++) {
		task_t task = task_avail[get_core_num()][i];

		if (!task || !task->ready || task->pri <= pri)
			continue;

		pri = task->pri;
	}

	if (INT_MIN == pri)
		return false;

	for (int i = 0; i < MAX_TASKS; i++) {
		task_t task = task_avail[get_core_num()][i];

		if (!task || !task->ready || task->pri < pri)
			continue;

		enum task_status status;
		status = setjmp(task_return[get_core_num()]);

		if (TASK_SAVE == status) {
			task_running[get_core_num()] = task;
			longjmp(task->regs, (int)task);
		}

		if (TASK_YIELD == status) {
			task_running[get_core_num()] = NULL;
			return true;
		}

		if (TASK_RETURN == status) {
			task_running[get_core_num()] = NULL;
			task_avail[get_core_num()][i] = NULL;

			if (task->memory)
				free(task->memory);

			return true;
		}

		panic("invalid setjmp status (%i)", status);
	}
}


task_t task_create(void (*fn)(void), void *stack, size_t size)
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
		if (!task_avail[get_core_num()][i]) {
			task_avail[get_core_num()][i] = task;
			return task;
		}
	}

	panic("Too many tasks on core %u (MAX_TASKS=%u)",
		get_core_num(), MAX_TASKS);
}

void task_yield(void)
{
	if (NULL == task_running[get_core_num()])
		panic("task_yield called from outside of a task");

	if (0 == setjmp(task_running[get_core_num()]->regs)) {
		longjmp(task_return[get_core_num()], TASK_YIELD);
	}
}


void task_yield_until_ready(void)
{
	if (NULL == task_running[get_core_num()])
		panic("task_yield_until_ready called from outside of a task");

	task_running[get_core_num()]->ready = false;
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


void task_yield_for(uint64_t us)
{
	if (NULL == task_running[get_core_num()])
		panic("task_yield_for called from outside of a task");

	task_t task = task_running[get_core_num()];
	(void)add_alarm_in_us(us, task_ready_alarm, task, true);
	task_yield_until_ready();
}


void task_yield_until(uint64_t us)
{
	if (NULL == task_running[get_core_num()])
		panic("task_yield_until called from outside of a task");

	task_t task = task_running[get_core_num()];
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
