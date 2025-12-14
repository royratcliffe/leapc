#include "leap.h"

#include <assert.h>

int is_leap_test(int argc, char **argv) {
  /*
   * What year is leap? What year is not leap?
   */
  assert(is_leap(0));
  assert(!is_leap(1970));
  return 0;
}
