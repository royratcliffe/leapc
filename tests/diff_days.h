/* SPDX-License-Identifier: MIT */
/*!
 * \file diff_days.h
 * \brief Function prototypes for computing day differences.
 * \copyright 2025, Roy Ratcliffe, Northumberland, United Kingdom
 */
#pragma once

/*!
 * \brief Compute difference in days between two years.
 * \param year1 Year to compute for.
 * \param year0 Base year for comparison.
 * \returns The difference between the "make time" days in-between the two years
 * and the leap_day() difference.
 */
double diff_days(int year1, int year0);
