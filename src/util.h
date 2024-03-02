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
} buffer_builder_t;

err_t buffer_read(const char *file_name, buffer_t *out);
err_t buffer_merge(size_t count, buffer_t *buffers, buffer_t *out);

buffer_builder_t *new_buffer_builder(void);
err_t buffer_builder_append(buffer_builder_t *self, buffer_t buffer);
void buffer_builder_build(buffer_builder_t *self, buffer_t *out);
void delete_buffer_builder(buffer_builder_t *self);
