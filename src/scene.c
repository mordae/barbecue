/*
 * Copyright (C) 2022 Jan Hamal Dvořák <mordae@anilinux.org>
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

#include "scene.h"

#include <pico/stdlib.h>


/* Stack of the active scenes. */
static scene_t stack;

/* Counter to indicate re-entrant calls. */
static unsigned depth = 0;


void scene_push(scene_t scene, void *arg)
{
	for (scene_t iter = stack; iter; iter = iter->next)
		if (scene == iter)
			panic("scene_push: same scene pushed twice");

	if (depth)
		panic("scene_push: called while modifying scene stack");

	scene->next = stack;
	stack = scene;

	depth++;

	if (scene->on_push)
		scene->on_push(arg);

	if (scene->on_show)
		scene->on_show();

	depth--;
}


void scene_pop(void)
{
	if (NULL == stack)
		panic("scene_pop: scene stack is empty");

	if (depth)
		panic("scene_pop: called while modifying scene stack");

	scene_t scene = stack;
	stack = scene->next;

	depth++;

	if (scene->on_hide)
		scene->on_hide();

	if (scene->on_pop)
		scene->on_pop();

	if (stack && stack->on_show)
		scene->on_show();

	depth--;
}


void scene_replace(scene_t scene, void *arg)
{
	if (NULL == stack)
		panic("scene_replace: scene stack is empty");

	if (depth)
		panic("scene_replace: called while modifying scene stack");

	scene_t prev = stack;
	stack = scene;
	scene->next = stack;

	depth++;

	if (prev->on_hide)
		prev->on_hide();

	if (prev->on_pop)
		prev->on_pop();

	if (scene->on_push)
		scene->on_push(arg);

	if (scene->on_show)
		scene->on_show();

	depth--;
}


bool scene_handle_switch(bool pressed)
{
	for (scene_t iter = stack; iter; iter = iter->next)
		if (iter->on_switch)
			if (iter->on_switch(pressed))
				return true;

	return false;
}


bool scene_handle_rotation(int steps)
{
	for (scene_t iter = stack; iter; iter = iter->next)
		if (iter->on_rotation)
			if (iter->on_rotation(steps))
				return true;

	return false;
}
