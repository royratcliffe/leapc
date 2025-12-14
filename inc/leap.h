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
 * \brief Leaped days completed up to but not including the first day of the
 * given year.
 * \param year The year to check.
 * \retval The number of leap days completed up to but not including the first
 * day of the given year.
 */
int leap_thru(int year);
