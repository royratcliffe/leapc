/* SPDX-License-Identifier: MIT */
/*!
 * \file leap.h
 * \brief Leap year function prototypes.
 * \copyright 2025, Roy Ratcliffe, Northumberland, United Kingdom
 */
#pragma once

#include <stdbool.h>

/*!
 * \brief Determine if a year is a leap year.
 * \details Is a year a leap year? A year is a leap year if it is divisible by
 * four, except for years that are divisible by 100, unless they are also
 * divisible by 400.
 * \param year The year to check.
 * \retval true if the year is a leap year.
 * \retval false if the year is not a leap year.
 */
bool is_leap(int year);

/*!
 * \brief Adds one for a leap year otherwise zero.
 * \details Answers 1 if the year is a leap year, otherwise answers 0. This is
 * the same result as is_leap() except that the result is an explicit integer; 1
 * for leap years, 0 for non-leap years.
 * \param year The year to check.
 * \retval 1 if the year is a leap year.
 * \retval 0 if the year is not a leap year.
 */
int leap_add(int year);

/*!
 * \brief Leaped days completed up to but not including the first day of the
 * given year.
 * \details Counts the number of leap days that have occurred from year 0 up to
 * but not including the first day of the given year. This is calculated as the
 * number of years divisible by 4, minus those divisible by 100, plus those
 * divisible by 400. This accounts for the rules of leap years in the Gregorian
 * calendar.
 * \param year The year to check.
 * \returns The number of leap days completed up to but not including the first
 * day of the given year.
 */
int leap_thru(int year);

/*!
 * \brief Counts leap-adjusted days up to some year.
 * \details Counts the number of days completed up to but not including the
 * first day of the year.
 * \param year The year to check.
 * \returns The number of leap-adjust days completed up to but not including the
 * first day of the given year.
 */
int leap_day(int year);

struct leap_off {
  int year;
  int day;
};

struct leap_off leap_off(int year, int day);
