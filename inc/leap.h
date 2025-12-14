#pragma once

#include <stdbool.h>

/*!
 * \brief Determine if a year is a leap year.
 * \details Is a year a leap year? A year is a leap year if it is divisible by
 * four, except for years that are divisible by 100, unless they are also
 * divisible by 400.
 * \param year The year to check.
 * \retval \c true if the year is a leap year.
 * \retval \c false if the year is not a leap year.
 */
bool is_leap(int year);
