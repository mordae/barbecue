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

#pragma once

#include <pico/types.h>
#include <hardware/platform_defs.h>

/* Maximum number of tasks on a single core. */
#if !defined(MAX_TASKS)
# define MAX_TASKS 16
#endif

#if !defined(__noreturn)
# define __noreturn  __attribute__((noreturn))
#endif


/* Private task data. */
typedef struct task *task_t;


/* Current tasks running on respective cores. */
extern task_t task_running[NUM_CORES];


/* Tasks assigned to respective cores. */
extern task_t task_avail[NUM_CORES][MAX_TASKS];


/*
 * Run a single task scheduled on the current core until it yields or returns.
 * Returns `false` when no task is ready.
 *
 * You might want to use `__wfe()` to put the core to sleep when there is
 * nothing more to do, but make sure to only call it after `task_run` has
 * returned `false`.
 *
 * This is what `task_run_loop` does.
 */
bool task_run(void);


/*
 * Run tasks on this core indefinitely.
 */
__noreturn void task_run_loop(void);


/*
 * Create new task with given stack.
 * Task private data are stored at the top of the stack.
 *
 * Minimum stack size (including internal task data) is 128 bytes.
 *
 * Recommended minimum value is 1024 bytes for when you do not plan to call
 * complex SDK functions. Allocating 4096 bytes should be enough for anything.
 *
 * If you do not give a stack pointer, it will be allocated and automatically
 * freed when the task returns.
 */
task_t task_create(void (*fn)(void), void *stack, size_t size);


/*
 * Pause current task and return to the scheduler.
 *
 * Task will remain ready to be resumed. This gives the scheduler an
 * opportunity to run higher priority tasks if needed.
 */
void task_yield(void);


/*
 * Same as `task_yield`, but gives way to a task of any priority.
 */
void task_yield_to_any(void);


/*
 * Pause current task and return to the scheduler.
 *
 * Task won't be resumed until marked ready. You need to set an alarm or some
 * other interrupt to mark it once it should be resumed. Or mark it ready from
 * another task.
 */
void task_yield_until_ready(void);


/* Yield task until given amount of microseconds elapses. */
void task_sleep_us(uint64_t us);


/* Yield task until given amount of milliseconds elapses. */
void task_sleep_ms(uint64_t ms);


/* Yield task until given time in microseconds. */
void task_yield_until(uint64_t us);


/* Mark given task as ready to continue. */
void task_set_ready(task_t task);


/* Manage task priority. Higher priority tasks run first. */
void task_set_priority(task_t task, int pri);
int task_get_priority(task_t task);


/* Manage task name of up to 8 bytes. */
void task_set_name(task_t task, const char *name);
void task_get_name(task_t task, char name[9]);
