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

int leap_add(int year) { return is_leap(year) ? 1 : 0; }

int leap_thru(int year) {
  /*
   * Expand the quotient terms first for debugging. Make it easier to see the
   * terms of the thru-sum.
   */
  const int q4 = quo_mod(year, 4).quo;
  const int q100 = quo_mod(year, 100).quo;
  const int q400 = quo_mod(year, 400).quo;
  return q4 - q100 + q400;
}
