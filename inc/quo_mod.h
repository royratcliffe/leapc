#pragma once

/*!
 * \brief Quotient and remainder in integer space.
 */
struct quo_mod {
  int quo, mod;
};

/*!
 * \brief Compute the integer quotient and modulus.
 * \details Performs an integer modulo operation.
 * \param x Numerator integer.
 * \param y Denominator integer. Must not be zero.
 * \return \c quo_mod structure.
 */
struct quo_mod quo_mod(int x, int y);
