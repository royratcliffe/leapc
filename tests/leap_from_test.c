#include "leap.h"

#include <assert.h>
#include <stdlib.h>

static inline bool equal_leap_date(struct leap_date lhs, struct leap_date rhs) {
  return lhs.year == rhs.year && lhs.month == rhs.month && lhs.day == rhs.day;
}

int leap_from_test(int argc, char **argv) {
  (void)argc;
  (void)argv;

  assert(equal_leap_date((struct leap_date){2024, 1, 1}, leap_date_from_off(leap_from(2024, 1, 1))));
  assert(equal_leap_date((struct leap_date){2023, 12, 1}, leap_date_from_off(leap_from(2024, 0, 1))));

  return EXIT_SUCCESS;
}
