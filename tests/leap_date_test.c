#include "leap.h"

#include <assert.h>
#include <stdlib.h>

int leap_date_test(int argc, char **argv) {
  (void)argc;
  (void)argv;

  assert(equal_leap_date((struct leap_date){1902, 9, 28}, leap_date(1902, 270)));
  assert(equal_leap_date((struct leap_date){1, 1, 1}, leap_date(1, 0)));
  assert(equal_leap_date((struct leap_date){2, 1, 1}, leap_date(1, 365)));
  assert(equal_leap_date((struct leap_date){1900, 12, 31}, leap_date(1900, 364)));

  return EXIT_SUCCESS;
}
