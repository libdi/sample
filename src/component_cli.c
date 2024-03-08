#include <stdio.h>
#include <stdlib.h>

#include "component.h"
#include "util.h"

int main(int argc, char **argv) {
  if (argc != 7) {
    fprintf(stderr,
            "usage: %s <data> <function body> <initializer function> "
            "<finalizer function> <dependency file> <out file>\n",
            argv[0]);
    exit(EXIT_FAILURE);
  }
  buffer_t data;
  if (di_internal_buffer_read(argv[1], &data))
    exit(EXIT_FAILURE);
  buffer_t function_body;
  if (di_internal_buffer_read(argv[2], &function_body))
    exit(EXIT_FAILURE);
  buffer_t initializer_function;
  if (di_internal_buffer_read(argv[3], &initializer_function))
    exit(EXIT_FAILURE);
  buffer_t finalizer_function;
  if (di_internal_buffer_read(argv[4], &finalizer_function))
    exit(EXIT_FAILURE);
  buffer_t dependency;
  if (di_internal_buffer_read(argv[5], &dependency))
    exit(EXIT_FAILURE);
  FILE *fp = fopen(argv[6], "wb");
  if (fp == NULL)
    exit(EXIT_FAILURE);
  size_t total_length;
  component_t *result =
      di_component(function_body, initializer_function, finalizer_function,
                   data, dependency, &total_length);
  if (!result)
    exit(EXIT_FAILURE);
  if (fwrite(result, 1, total_length, fp) != total_length) {
    remove(argv[6]);
    exit(EXIT_FAILURE);
  }
}
