/* SPDX-License-Identifier: MIT */
/*!
 * \file quo_mod.h
 * \brief Quotient and modulus prototypes.
 * \details Header file for quotient and modulus function implementations.
 * \copyright 2025, Roy Ratcliffe, Northumberland, United Kingdom
 */

#ifndef __QUO_MOD_H__
#define __QUO_MOD_H__

/*!
 * \brief Quotient and remainder in integer space.
 * \details Structure encapsulating the integer quotient and modulus.
 * The structure is returned by the \c quo_mod() function.
 *
 * This structure mirrors the standard C \c div_t structure returned by the
 * \c div() function, but uses different member names.
 *
 * \see quo_mod()
 */
struct quo_mod {
  /*!
   * \brief Integer quotient.
   */
  int quo;
  /*!
   * \brief Integer modulus.
   */
  int mod;
};

/*!
 * \brief Compute the integer quotient and modulus.
 * \details Performs an integer modulo operation. Then subtracts the modulus from
 * the numerator and applies an integer division in order to compute the
 * quotient.
 *
 * The following invariant proves true: the numerator matches the denominator
 * multiplied by the quotient plus the modulus.
 * \code
 * struct quo_mod qm = quo_mod(x, y);
 * x == (y * qm.quo + qm.mod);
 * \endcode
 * \param x Numerator integer.
 * \param y Denominator integer. Must not be zero.
 * \return \c quo_mod structure comprising the quotient and modulus.
 * \remarks Like Lua's modulo operator, this function ensures that the
 * modulus is always non-negative when the denominator is positive, and always
 * non-positive when the denominator is negative.
 * \note The \c quo_mod identifier exists in structure namespace as well as
 * function namespace.
 * \warning Throws a division-by-zero error if the denominator \c y is zero.
 */
struct quo_mod quo_mod(int x, int y);

#endif /* __QUO_MOD_H__ */
