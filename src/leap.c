/* SPDX-License-Identifier: MIT */
/*!
 * \file leap.c
 * \brief Leap year function implementations.
 * \details Implements functions to determine if a year is a leap year, count
 * leap years up to a given year, and calculate leap-adjusted days.
 * \copyright 2025, Roy Ratcliffe, Northumberland, United Kingdom
 */
#include "leap.h"
#include "quo_mod.h"

bool is_leap(int year) {
  /*
   * Allow C99's standard precedence to rule over operator ordering: modulo
   * exceeds equality and inequality operators. No need for brackets except
   * perhaps to meet some external standard that requires brackets
   * pendantically.
   *
   * A year is a leap year if it is divisible by 4, except for years that
   * are divisible by 100, unless they are also divisible by 400. Optimisation
   * using the \c & operator is possible but reduces readability. Instead, rely
   * on compiler optimisation.
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

int leap_day(int year) { return year * 365 + leap_thru(year - 1) + 1; }

struct leap_off leap_off(int year, int day) {
  int days = 365 + leap_add(year);
  while (day < 0 || day >= days) {
    int year0 = year + quo_mod(day, days).quo;
    day += leap_day(year) - leap_day(year0);
    year = year0;
    days = 365 + leap_add(year);
  }
  return (struct leap_off){.year = year, .day = day};
}
