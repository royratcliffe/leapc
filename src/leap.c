#include "leap.h"

bool is_leap(int year) {
  return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}
