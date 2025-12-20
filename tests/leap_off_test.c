#include "leap.h"

#include <assert.h>
#include <stdlib.h>

int leap_off_test(int argc, char **argv) {
  assert(equal_leap_off((struct leap_off){0, 365}, leap_off(1, -1)));
  assert(equal_leap_off((struct leap_off){1, 0}, leap_off(1, 0)));

  /*
   * Negative day offset that normalises to previous year.
   * Year 5 offset -1 day normalises to year 4 day 365 (leap year).
   */
  assert(equal_leap_off((struct leap_off){4, 365}, leap_off(5, -1)));

  assert(equal_leap_off((struct leap_off){5, 0}, leap_off(4, 366)));
  assert(equal_leap_off((struct leap_off){2024, 365}, leap_off(2024, 365)));
  assert(equal_leap_off((struct leap_off){2025, 0}, leap_off(2024, 366)));
  assert(equal_leap_off((struct leap_off){1902, 270}, leap_off(1900, 1000)));
  assert(equal_leap_off((struct leap_off){1900, 0}, leap_off(0, LEAP_MCM)));
  assert(equal_leap_off((struct leap_off){1970, 0}, leap_off(0, leap_day(1970))));
  assert(equal_leap_off((struct leap_off){10, 0}, leap_off(1970, -leap_day(1960))));
  return EXIT_SUCCESS;
}
