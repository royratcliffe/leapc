#include "leap.h"

#include <assert.h>
#include <stdlib.h>

int leap_absdate_test(int argc, char **argv) {
  (void)argc;
  (void)argv;

  assert(equal_leap_date((struct leap_date){0, 1, 1}, leap_absdate(0)));
  assert(equal_leap_date((struct leap_date){1970, 1, 1}, leap_absdate(leap_absfrom(1970, 1, 1))));
  assert(equal_leap_date((struct leap_date){1970, 2, 1}, leap_absdate(leap_absfrom(1970, 1, 31) + 1)));

  return EXIT_SUCCESS;
}
