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

#if !defined(__ASSEMBLER__)

#define lock_internal_spin_unlock_with_best_effort_wait_or_timeout(lock, save, until) \
	task_lock_spin_unlock_with_timeout((lock)->spin_lock, (save), (until))

#define lock_internal_spin_unlock_with_notify(lock, save) \
	task_lock_spin_unlock_with_notify((lock)->spin_lock, (save))

#define lock_internal_spin_unlock_with_wait(lock, save) \
	task_lock_spin_unlock_with_wait((lock)->spin_lock, (save))

#define sync_internal_yield_until_before(until) \
	task_sync_yield_until_before((until))


int task_lock_spin_unlock_with_timeout(volatile unsigned long *, unsigned long, unsigned long long);
void task_lock_spin_unlock_with_notify(volatile unsigned long *, unsigned long);
void task_lock_spin_unlock_with_wait(volatile unsigned long *, unsigned long);
void task_sync_yield_until_before(unsigned long long);

#endif
