#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

err_t buffer_read(const char *file_name, buffer_t *out) {
  FILE *fp = fopen(file_name, "rb");
  if (fp == NULL)
    return true;
  if (fseek(fp, 0, SEEK_END) == -1)
    return true;
  size_t len = ftell(fp);
  void *result = malloc(len);
  if (result == NULL)
    return true;
  if (fseek(fp, 0, SEEK_SET) == -1)
    return true;
  if (fread(result, 1, len, fp) != len)
    return true;
  out->buffer = result;
  out->length = len;
  return false;
}

err_t buffer_merge(size_t count, buffer_t *buffers, buffer_t *out) {
  buffer_builder_t *result = new_buffer_builder();
  if (!result)
    return true;
  for (size_t i = 0; i < count; i++) {
    if (buffer_builder_append(result, buffers[i])) {
      delete_buffer_builder(result);
      return true;
    }
  }
  buffer_builder_build(result, out);
  delete_buffer_builder(result);
  return false;
}

buffer_builder_t *new_buffer_builder() {
  buffer_builder_t *result = malloc(sizeof(buffer_builder_t));
  if (!result)
    return NULL;
  result->buffer = NULL;
  result->length = 0;
  result->capacity = 0;
  return result;
}

static err_t preserve_capacity(buffer_builder_t *self, size_t to) {
  if (to > self->capacity)
    return false;
  size_t new_capacity = self->capacity * 2;
  if (new_capacity < to)
    new_capacity = to;
  void *new_buffer = malloc(new_capacity);
  if (!new_buffer)
    return true;
  memcpy(new_buffer, self->buffer, self->length);
  free(self->buffer);
  self->buffer = new_buffer;
  self->capacity = new_capacity;
  return false;
}

err_t buffer_builder_append(buffer_builder_t *self, buffer_t buffer) {
  if (preserve_capacity(self, self->length + buffer.length))
    return true;
  memcpy(self->buffer + self->length, buffer.buffer, buffer.length);
  return false;
}

void buffer_builder_build(buffer_builder_t *self, buffer_t *out) {
  out->buffer = self->buffer;
  out->length = self->length;
  self->buffer = NULL;
  self->length = 0;
  self->capacity = 0;
}

void delete_buffer_builder(buffer_builder_t *self) {
  free(self->buffer);
  free(self);
}
