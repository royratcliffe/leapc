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

/*
 * The `+ 1` anchors the epoch: year 0 maps to day 0. The term `year * 365 +
 * leap_thru(year - 1)` counts days up to (but not including) the target year.
 * Without the `+ 1`, `leap_day(0)` would be `-1`. Adding `1` fixes this:
 * `leap_day(0) == 0` and `leap_day(1) == 366`. Constant offsets cancel in
 * subtractions, preserving year differences.
 */
int leap_day(int year) { return year * 365 + leap_thru(year - 1) + 1; }

/*
 * Normalises an arbitrary day offset relative to a given year into a canonical
 * (year, day-of-year) pair where 0 <= day < days_in_year.
 *
 * Algorithm:
 *  - Compute the current year's length: `days = 365 + leap_add(year)`.
 *  - While `day` lies outside `[0, days)`:
 *      * Jump whole years using floor-like quotient semantics:
 *        `year0 = year + quo_mod(day, days).quo`.
 *      * Rebase the offset to the new year using absolute day counts:
 *        `day += leap_day(year) - leap_day(year0)`.
 *      * Update `year` to `year0` and recompute `days` for that year.
 *  - Return the resulting `(year, day)` which is within the year's bounds.
 *
 * Notes:
 *  - `quo_mod` uses Lua-style modulo semantics so negative offsets jump the
 *    correct number of whole years in the negative direction.
 *  - Differences of `leap_day(...)` cancel the constant epoch offset, ensuring
 *    exact rebasing regardless of the `+1` anchor in `leap_day`.
 */
struct leap_off leap_off(int year, int day) {
  int days = 365 + leap_add(year);
  while (day < 0 || day >= days) {
    int year0 = year + quo_mod(day, days).quo;
    day += leap_day(year) - leap_day(year0);
    days = 365 + leap_add(year = year0);
  }
  return (struct leap_off){.year = year, .day = day};
}

int leap_mday(int year, int month) {
  static const int MDAY[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  const struct quo_mod qm = quo_mod(month - 1, 12);
  return MDAY[qm.mod] + (month == 2 ? leap_add(year + qm.quo) : 0);
}

int leap_yday(int year, int month) {
  static const int YDAY[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
  const struct quo_mod qm = quo_mod(month - 1, 12);
  return YDAY[qm.mod] + (month > 2 ? leap_add(year + qm.quo) : 0);
}

/*
 * Converts a (year, day-of-year) pair into a (year, month, day-of-month)
 * triple.
 *
 * Algorithm:
 *  - Normalise the (year, day) pair using leap_off to ensure day is within
 *    year's bounds.
 *  - Iterate months from 1 to 12, subtracting the number of days in each month
 *    from day until day is less than the number of days in the current month.
 *  - The current month is the target month, and day + 1 is the target day of
 *    month (to convert from 0-based to 1-based).
 */
struct leap_date leap_date(int year, int day) {
  struct leap_off off = leap_off(year, day);
  int month = 1;
  for (; month <= 12; ++month) {
    const int mday = leap_mday(off.year, month);
    if (off.day < mday) {
      break;
    }
    off.day -= mday;
  }
  return (struct leap_date){
      .year = off.year,
      .month = month,
      .day = off.day + 1,
  };
}

struct leap_date leap_date_from_off(struct leap_off off) {
  return leap_date(off.year, off.day);
}

struct leap_off leap_from(int year, int month, int day) {
  const struct quo_mod qm = quo_mod(month - 1, 12);
  year += qm.quo;
  return leap_off(year, leap_yday(year, qm.mod + 1) + day - 1);
}

struct leap_date leap_absdate(int day) {
  return leap_date(0, day);
}

int leap_absfrom(int year, int month, int day) {
  struct leap_off off = leap_from(year, month, day);
  return leap_day(off.year) + off.day;
}
