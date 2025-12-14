/* SPDX-License-Identifier: MIT */
/*!
 * \file days.h
 * \brief Function prototypes for making days from standard time and computing
 * day differences.
 * \copyright 2025, Roy Ratcliffe, Northumberland, United Kingdom
 */
#pragma once

/*!
 * \brief Days of year, month and day of month.
 * \details Uses the standard library's "make time" function to make the number
 * of days for a year, month and month day. Divides the seconds by 86,400 (the
 * number of seconds in a day) in order to answer days rather than seconds.
 * \param year Year from 1970.
 * \param mon One-based month. Converts to a zero-based month.
 * \param mday Day of the month starting at one.
 * \note The standard library's mktime() function has a prescribed minimum start
 * time of 1970. Times cannot precede the first day of that year.
 */
double mkdays(int year, int mon, int mday);

/*!
 * \brief Compute difference in days between two years.
 * \param year1 Year to compute for.
 * \param year0 Base year for comparison.
 * \returns The difference between the "make time" days in-between the two years
 * and the leap_day() difference.
 */
double diff_days(int year1, int year0);
