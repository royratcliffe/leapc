#include "leap.h"

bool is_leap(int year) {
  /*
   * Allow C99's standard precedence to rule over operator ordering: modulo
   * exceeds equality and inequality operators.
   */
  return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}
