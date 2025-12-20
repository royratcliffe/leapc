#include "leap.h"

#include <assert.h>
#include <stdlib.h>

int leap_from_test(int argc, char **argv) {
  (void)argc;
  (void)argv;

  assert(equal_leap_date((struct leap_date){2024, 1, 1}, leap_date_from_off(leap_from(2024, 1, 1))));
  assert(equal_leap_date((struct leap_date){2023, 12, 1}, leap_date_from_off(leap_from(2024, 0, 1))));
  assert(equal_leap_date((struct leap_date){2023, 11, 30}, leap_date_from_off(leap_from(2024, 0, 0))));

  return EXIT_SUCCESS;
}
