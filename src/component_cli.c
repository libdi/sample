#include <stdio.h>
#include <stdlib.h>

#include "component.h"
#include "util.h"

int main(int argc, char **argv) {
  if (argc != 6) {
    fprintf(stderr,
            "usage: %s <data> <function body> <initializer function> "
            "<finalizer function> <dependency file>\n",
            argv[0]);
    exit(EXIT_FAILURE);
  }
  di_internal_buffer_t data;
  if (buffer_read(argv[1], &data))
    exit(EXIT_FAILURE);
  di_internal_buffer_t function_body;
  if (buffer_read(argv[2], &function_body))
    exit(EXIT_FAILURE);
  di_internal_buffer_t initializer_function;
  if (buffer_read(argv[3], &initializer_function))
    exit(EXIT_FAILURE);
  di_internal_buffer_t finalizer_function;
  if (buffer_read(argv[4], &finalizer_function))
    exit(EXIT_FAILURE);
  di_internal_buffer_t dependency;
  if (buffer_read(argv[5], &dependency))
    exit(EXIT_FAILURE);
  // WIP: ...
}
