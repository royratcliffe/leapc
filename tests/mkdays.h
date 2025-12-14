/* SPDX-License-Identifier: MIT */
/*!
 * \file mkdays.h
 * \brief Function prototypes for making days from standard time.
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
