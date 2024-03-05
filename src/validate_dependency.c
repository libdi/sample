#include "validate_dependency.h"

err_t di_validate_dependency(buffer_t buffer, uint_fast16_t *out_count) {
  uint_fast16_t result = 0;
  byte_t *buf = buffer.buffer;
  size_t current_position = 0;
  while (current_position != buffer.length) {
    if (current_position > buffer.length)
      return true;
    current_position +=
        (buf[current_position] == 0 ? 2 : buf[current_position]) + 1;
  }
  *out_count = result;
  return false;
}
