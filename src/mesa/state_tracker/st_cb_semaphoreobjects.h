/*
 * Copyright © 2017 Valve Corporation.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef ST_CB_SEMAPHOREOBJECTS_H
#define ST_CB_SEMAPHOREOBJECTS_H

#include "util/compiler.h"
#include "main/mtypes.h"

struct dd_function_table;
struct pipe_screen;

struct st_semaphore_object
{
   struct gl_semaphore_object Base;
   struct pipe_fence_handle *fence;
};

static inline struct st_semaphore_object *
st_semaphore_object(struct gl_semaphore_object *obj)
{
   return (struct st_semaphore_object *)obj;
}

struct gl_semaphore_object *
st_semaphoreobj_alloc(struct gl_context *ctx, GLuint name);
void
st_semaphoreobj_free(struct gl_context *ctx,
                     struct gl_semaphore_object *semObj);

void
st_import_semaphoreobj_fd(struct gl_context *ctx,
                          struct gl_semaphore_object *semObj,
                          int fd);

void
st_server_wait_semaphore(struct gl_context *ctx,
                         struct gl_semaphore_object *semObj,
                         GLuint numBufferBarriers,
                         struct gl_buffer_object **bufObjs,
                         GLuint numTextureBarriers,
                         struct gl_texture_object **texObjs,
                         const GLenum *srcLayouts);

void
st_server_signal_semaphore(struct gl_context *ctx,
                           struct gl_semaphore_object *semObj,
                           GLuint numBufferBarriers,
                           struct gl_buffer_object **bufObjs,
                           GLuint numTextureBarriers,
                           struct gl_texture_object **texObjs,
                           const GLenum *dstLayouts);
#endif
