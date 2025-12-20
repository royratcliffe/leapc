/* SPDX-License-Identifier: MIT */
/*!
 * \file leap.h
 * \brief Leap year function prototypes.
 * \details Provides functions to determine if a year is a leap year, count leap
 * years up to a given year, and calculate leap-adjusted days.
 * \copyright 2025, Roy Ratcliffe, Northumberland, United Kingdom
 */

#ifndef __LEAP_H__
#define __LEAP_H__

#include <stdbool.h>

/*!
 * \brief Leap offset at 1900.
 * \details MCM is Roman numerals for 1900.
 */
#define LEAP_MCM 693961

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
 *
 * Compute the number of days in a given year as:
 * \code
 * 365 + leap_add(year);
 * \endcode
 * \param year The year to check.
 * \retval 1 if the year is a leap year.
 * \retval 0 if the year is not a leap year.
 */
int leap_add(int year);

/*!
 * \brief Leap years completed from year 0 up to but not including the first day
 * of the specified year.
 * \details Counts the number of leap years that have occurred from year 0 up to
 * but not including the first day of the given year. This is calculated as the
 * number of years divisible by 4, minus those divisible by 100, plus those
 * divisible by 400. This accounts for the rules of leap years in the Gregorian
 * calendar.
 * \param year The target year up to which leap years should be counted.
 * \returns The total number of leap years from year 0 through the specified
 * year.
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

/*!
 * \brief Leap offset by year and day.
 * \details Represents a (year, day-of-year) pair where day-of-year is
 * guaranteed to be within the bounds of the year: 0 <= day < 365 or 366.
 */
struct leap_off {
  /*!
   * \brief Year offset.
   */
  int year;
  /*!
   * \brief Day of year offset.
   */
  int day;
};

/*!
 * \brief Compares two leap_off structures for equality.
 * \details Checks if two leap_off structures represent the same offset by
 * comparing their year and day offset fields.
 * \param lhs The first leap_off structure.
 * \param rhs The second leap_off structure.
 * \retval true if both structures represent the same offset.
 * \retval false otherwise.
 * \note C cannot directly compare structures; the compiler reports "invalid
 * operands to binary expression" errors. For example, the following code
 * \code
 * (struct leap_off){2020, 59} == leap_off(2020, 59)
 * \endcode
 * produces such an error.
 * So, provide a helper function to compare two leap_off structures.
 * Compile-time inlining should eliminate any performance penalty.
 */
static inline bool equal_leap_off(struct leap_off lhs, struct leap_off rhs) {
  return lhs.year == rhs.year && lhs.day == rhs.day;
}

/*!
 * \brief Offsets year and day of year.
 * \details Year and day of year from year and day of year. Adjust the day so
 * that it sits in-between 0 and 365 or 366, inclusively.
 *
 * The day adjusts to be within the range of 0 to 365 or 366 inclusively, and
 * the year is adjusted accordingly.
 *
 * This function ensures that the day of the year does not exceed the number of
 * days in the year, accounting for leap years. If the day is negative or
 * exceeds the number of days in the year, it adjusts the year and day
 * accordingly. The day is adjusted to be 0-based, meaning it starts from 0 for
 * the first day of the year. The year is adjusted to account for the number of
 * days in the year, which can be either 365 or 366 depending on whether it is a
 * leap year.
 * \param year The year.
 * \param day_off The day of the year offset, starting from 0.
 * \retval leap_off.year The year adjusted to account for the number of days in
 * the year.
 * \retval leap_off.day The adjusted day of the year, starting from 0 for the
 * first day.
 */
struct leap_off leap_off(int year, int day_off);

/*!
 * \brief Day of month from year and month.
 * \details Returns the number of days in the month for the given year and
 * month. Accounts for leap years in February.
 * \param year The year.
 * \param month The month, starting from 1 for January.
 * \retval The number of days in the month, accounting for leap years in
 * February.
 */
int leap_mday(int year, int month);

/*!
 * \brief Day of year from year and month.
 * \details Returns the day of the year for the given year and month. The day of
 * the year is calculated by summing the days in the months up to the given
 * month, and adding an extra day if the month is after February in a leap year.
 * \param year The year.
 * \param month The month, starting from 1 for January.
 * \retval The day of the year, starting from 0 for first of January.
 */
int leap_yday(int year, int month);

/*!
 * \brief Leap year date structure.
 * \details Represents a date in terms of year, month, and day of month,
 * accounting for leap years.
 */
struct leap_date {
  /*!
   * \brief Year.
   */
  int year;
  /*!
   * \brief Month of year starting from 1 for January.
   */
  int month;
  /*!
   * \brief Day of month starting from 1 for the first day of the month.
   */
  int day;
};

/*!
 * \brief Compares two leap_date structures for equality.
 * \details Checks if two leap_date structures represent the same date by
 * comparing their year, month, and day fields.
 * \param lhs The first leap_date structure.
 * \param rhs The second leap_date structure.
 * \retval true if both structures represent the same date.
 * \retval false otherwise.
 */
static inline bool equal_leap_date(struct leap_date lhs, struct leap_date rhs) {
  return lhs.year == rhs.year && lhs.month == rhs.month && lhs.day == rhs.day;
}

/*!
 * \brief Date from year and day of year.
 * \details Adjust the day so that it sits in-between 1 and 365 (or 366) inclusively.
 * Returns the year, month, and day of the month for the given year and day of
 * year. The day of the month is adjusted to be 1-based, meaning it starts from 1
 * for the first day of the month.
 * \param year The year.
 * \param day_off Day of the year offset, starting from 0 for first of January.
 * \retval leap_date.year The year.
 * \retval leap_date.month The month, starting from 1 for January.
 * \retval leap_date.day The day of the month, starting from 1 for the first day
 * of the month.
 */
struct leap_date leap_date(int year, int day_off);

/*!
 * \brief Date from leap offset.
 * \details Converts a leap_off structure to a leap_date structure.
 * \param off The leap_off structure containing year and day of year.
 * \return The corresponding leap_date structure.
 */
static inline struct leap_date leap_date_from_off(struct leap_off off) { return leap_date(off.year, off.day); }

/*!
 * \brief Day from year, month and day of month.
 * \details Adjusts the month so that it sits in-between 1 and 12 inclusively.
 * The month offsets the year. Returns the absolute date from the given year,
 * month, and day of month.
 * \param year The year.
 * \param month The month, starting from 1 for January.
 * \param day The one-based day of the month, starting from 1 for the first day
 * of the month.
 * \returns The absolute date as the number of days since the epoch.
 */
struct leap_off leap_from(int year, int month, int day);

/*!
 * \brief Day from leap date.
 * \details Converts a leap_date structure to a leap_off structure.
 * \param date The leap_date structure containing year, month, and day of month.
 * \returns The corresponding leap_off structure. The absolute date as the
 * number of days since the epoch.
 */
static inline struct leap_off leap_from_date(struct leap_date date) {
  return leap_from(date.year, date.month, date.day);
}

/*!
 * \brief Absolute date from day of year.
 * \details Returns the absolute date from the given day of year, starting from
 * 0 for the first day of the year. The absolute date is calculated as the
 * number of days since the epoch (January 1, 1970).
 * \param day_off The day of the year offset, starting from 0 for the first day
 * of the year.
 * \returns The absolute date as the number of days since the epoch.
 */
struct leap_date leap_abs_date(int day_off);

/*!
 * \brief Absolute date from year, month, and day of month.
 * \details Returns the absolute date from the given year, month, and day of
 * month. The absolute date is calculated as the number of days since the epoch
 * (January 1, 1970).
 * \param year The year.
 * \param month The month, starting from 1 for January.
 * \param day Day of the month, starting from 1 for the first day of the month.
 * \returns The absolute date as the number of days since the epoch.
 */
int leap_abs_from(int year, int month, int day);

#endif /* __LEAP_H__ */
