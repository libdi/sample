#pragma once

#include <stdbool.h>
#include <stddef.h>

typedef bool err_t;
typedef signed char byte_t;

typedef struct buffer {
  void *buffer;
  size_t length;
} buffer_t;

typedef struct buffer_builder {
  void *buffer;
  size_t length;
  size_t capacity;
} builder_t;

err_t di_internal_buffer_read(const char *file_name, buffer_t *out);
err_t di_internal_buffer_merge(size_t count, buffer_t *buffers, buffer_t *out);

builder_t *di_internal_new_builder(void);
err_t di_internal_builder_append(builder_t *self, buffer_t buffer);
void di_internal_builder_build(builder_t *self, buffer_t *out);
void di_internal_delete_builder(builder_t *self);
