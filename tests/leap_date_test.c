#include "leap.h"

#include <assert.h>
#include <stdlib.h>

int leap_date_test(int argc, char **argv) {
  (void)argc;
  (void)argv;

  assert(equal_leap_date((struct leap_date){1902, 9, 28}, leap_date(1902, 270)));
  assert(equal_leap_date((struct leap_date){1, 1, 1}, leap_date(1, 0)));
  assert(equal_leap_date((struct leap_date){2, 1, 1}, leap_date(1, 365)));

  /*
   * Three hundred and sixty five days from midnight on 1900-01-01 is 1900-12-31
   * since 1900 is not a leap year.
   */
  assert(equal_leap_date((struct leap_date){1900, 12, 31}, leap_date(1900, 364)));

  return EXIT_SUCCESS;
}
