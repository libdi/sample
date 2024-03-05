#pragma once

#include <stdint.h>

#include "util.h"

err_t di_validate_dependency(buffer_t buffer, uint_fast16_t *out_count);
