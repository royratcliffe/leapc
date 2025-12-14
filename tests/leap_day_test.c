#include "leap.h"

#include <assert.h>

int leap_day_test(int argc, char **argv) {
  assert(366 == leap_day(1));
  assert(693961 == leap_day(1900));
  return 0;
}
