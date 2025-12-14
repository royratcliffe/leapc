#include "leap.h"
#include "quo_mod.h"

bool is_leap(int year) {
  /*
   * Allow C99's standard precedence to rule over operator ordering: modulo
   * exceeds equality and inequality operators. No need for brackets except
   * perhaps to meet some external standard that requires brackets
   * pendantically.
   */
  return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

int leap_thru(int year) {
  return quo_mod(year, 4).quo - quo_mod(year, 100).quo + quo_mod(year, 400).quo;
}
