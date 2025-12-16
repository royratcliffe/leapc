#include "leap.h"

#include <assert.h>

int leap_thru_test(int argc, char **argv) {
  assert(0 == leap_thru(0));
  assert(0 == leap_thru(1));
  assert(0 == leap_thru(2));
  assert(0 == leap_thru(3));
  assert(1 == leap_thru(4));
  assert(24 == leap_thru(100));
  assert(97 == leap_thru(400));
  assert(693960 == 1900 * 365 + leap_thru(1900));
  return 0;
}
