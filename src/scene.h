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

#pragma once

#include <pico/types.h>

/*
 * Scene virtual function table.
 *
 * It has no private data, because we assume they are stored statically
 * inside the respective module.
 */
struct scene {
	/*
	 * Called when the scene enters the scene stack,
	 * before `on_show` is called.
	 */
	void (*on_push)(void *arg);

	/*
	 * Called when the scene leaves the scene stack,
	 * after `on_hide` is called.
	 */
	void (*on_pop)(void);

	/*
	 * Called when the scene appears at the top of the stack.
	 */
	void (*on_show)(void);

	/*
	 * Called when the scene gets covered by another.
	 */
	void (*on_hide)(void);

	/*
	 * Called when the switch state changes.
	 *
	 * Returns `true` when the event was handled and should not be
	 * propagated to the lower scenes in the stack.
	 */
	bool (*on_switch)(bool pressed);

	/*
	 * Called when the rotary encoder is rotated.
	 * Steps are either positive or negative.
	 *
	 * Returns `true` when the event was handled and should not be
	 * propagated to the lower scenes in the stack.
	 */
	bool (*on_rotation)(int steps);

	/*
	 * Next scene in the stack.
	 * You should not touch this field.
	 */
	struct scene *next;
};


typedef struct scene *scene_t;


/*
 * Push a scene to the scene stack.
 *
 * Same scene must not be pushed to the scene stack twice!
 */
void scene_push(scene_t scene, void *arg);


/* Pop a scene from the scene stack. */
void scene_pop(void);


/*
 * Replace the scene at the top of the scene stack.
 *
 * Similar to scene_pop() followed by a scene_push(), except the scene
 * below the one being replaced does not receive `on_show`.
 */
void scene_replace(scene_t scene, void *arg);


/* Let scene stack handle a switch event. */
bool scene_handle_switch(bool pressed);


/* Let scene stack handle a rotation event. */
bool scene_handle_rotation(int steps);
