#include "leap.h"

#include <assert.h>
#include <stdlib.h>

int leap_absfrom_test(int argc, char **argv) {
  (void)argc;
  (void)argv;

  assert(0 == leap_absfrom(0, 1, 1));

  return EXIT_SUCCESS;
}
