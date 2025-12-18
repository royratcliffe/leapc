#include "leap.h"

#include <assert.h>
#include <stdlib.h>

/*
 * C cannot directly compare structures; the compiler reports "invalid
 * operands to binary expression" errors. For example:
 *
 *     (struct leap_off){2020, 59} == leap_off(2020, 59)
 *
 * So, provide a helper function to compare two leap_off structures.
 * Compile-time inlining should eliminate any performance penalty.
 */
static inline bool equal_leap_off(struct leap_off lhs, struct leap_off rhs) {
  return lhs.year == rhs.year && lhs.day == rhs.day;
}

int leap_off_test(int argc, char **argv) {
  assert(equal_leap_off((struct leap_off){0, 365}, leap_off(1, -1)));
  assert(equal_leap_off((struct leap_off){1, 0}, leap_off(1, 0)));
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
