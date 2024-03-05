#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "validate_dependency.h"

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "usage: %s <file to validate>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  buffer_t content;
  if (di_internal_buffer_read(argv[1], &content))
    exit(EXIT_FAILURE);
  uint_fast16_t unused;
  if (di_validate_dependency(content, &unused))
    exit(EXIT_FAILURE);
  free(content.buffer);
}
