#pragma once

#include <stdint.h>

#pragma pack(push, 1)
typedef struct head {
  uint32_t size_of_function_body;
  uint32_t size_of_initializer_function;
  uint32_t size_of_finalizer_function;
  uint32_t size_of_data;
  uint16_t number_of_dependencies;
  char data[];
} head_t;
#pragma pack(pop)
