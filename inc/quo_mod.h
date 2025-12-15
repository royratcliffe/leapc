/* SPDX-License-Identifier: MIT */
/*!
 * \file quo_mod.h
 * \brief Quotient and modulus prototypes.
 * \details Header file for quotient and modulus function implementations.
 * \copyright 2025, Roy Ratcliffe, Northumberland, United Kingdom
 */
#pragma once

/*!
 * \brief Quotient and remainder in integer space.
 */
struct quo_mod {
  int quo; /*!< Integer quotient. */
  int mod; /*!< Integer modulus. */
};

/*!
 * \brief Compute the integer quotient and modulus.
 * \details Performs an integer modulo operation. Then subtracts the modulus from
 * the numerator and applies an integer division in order to compute the
 * quotient.
 *
 * The following proves true: the numerator matches the denominator multiplied
 * by the quotient plus the modulus.
 * \code
 * struct quo_mod qm = quo_mod(x, y);
 * x == (y * qm.quo + qm.mod);
 * \endcode
 * \param x Numerator integer.
 * \param y Denominator integer. Must not be zero.
 * \return \c quo_mod structure comprising the quotient and modulus.
 * \note The \c quo_mod identifier exists in structure namespace as well as
 * function namespace.
 * \warning Throws a division-by-zero error if the denominator \c y is zero.
 */
struct quo_mod quo_mod(int x, int y);
