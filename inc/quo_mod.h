#pragma once

/*!
 * \brief Quotient and remainder in integer space.
 */
struct quo_mod {
  int quo, mod;
};

/*!
 * \brief Compute the integer quotient and modulus.
 * \details Performs an integer modulo operation. Then subtracts the modulo from
 * the numerator and applies an integer division.
 * \code
 * struct quo_mod qm = quo_mod(x, y);
 * x == (y * qm.quo + qm.mod);
 * \endcode
 * \param x Numerator integer.
 * \param y Denominator integer. Must not be zero.
 * \return \c quo_mod structure.
 * \note The \c quo_mod identifier exists in structure namespace as well as
 * function namespace.
 */
struct quo_mod quo_mod(int x, int y);
