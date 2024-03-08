#include "component.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "validate_dependency.h"

component_t *di_component(buffer_t function_body, buffer_t initializer_function,
                          buffer_t finalizer_function, buffer_t data,
                          buffer_t dependencies, size_t *out_total_length) {
  uint16_t count;
  uint_fast16_t tmp;
  if (di_validate_dependency(dependencies, &tmp))
    return NULL;
  count = tmp;
  *out_total_length = sizeof(component_t) + dependencies.length +
                      function_body.length + initializer_function.length +
                      finalizer_function.length + data.length;
  component_t *result = malloc(*out_total_length);
  if (result == NULL)
    return NULL;
  result->size_of_function_body = function_body.length;
  result->size_of_initializer_function = initializer_function.length;
  result->size_of_finalizer_function = finalizer_function.length;
  result->size_of_data = data.length;
  result->number_of_dependencies = count;
  char *current_position = &result->data[0];
  memcpy(current_position, dependencies.buffer, dependencies.length);
  current_position += dependencies.length;
  memcpy(current_position, function_body.buffer, function_body.length);
  current_position += function_body.length;
  memcpy(current_position, initializer_function.buffer,
         initializer_function.length);
  current_position += initializer_function.length;
  memcpy(current_position, finalizer_function.buffer,
         finalizer_function.length);
  current_position += finalizer_function.length;
  memcpy(current_position, data.buffer, data.length);
  return result;
}
