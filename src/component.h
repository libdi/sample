#pragma once

#include <stdint.h>

#include "util.h"

#pragma pack(push, 1)
typedef struct component {
  uint32_t size_of_function_body;
  uint32_t size_of_initializer_function;
  uint32_t size_of_finalizer_function;
  uint32_t size_of_data;
  uint16_t number_of_dependencies;
  char data[];
} component_t;
#pragma pack(pop)

component_t *di_component(buffer_t function_body, buffer_t initializer_function,
                          buffer_t finalizer_function, buffer_t data,
                          buffer_t dependencies, size_t *out_total_length);
