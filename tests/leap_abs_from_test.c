#include "leap.h"

#include <assert.h>
#include <stdlib.h>

int leap_abs_from_test(int argc, char **argv) {
  (void)argc;
  (void)argv;

  assert(0 == leap_abs_from(0, 1, 1));

  return EXIT_SUCCESS;
}
