/* SPDX-License-Identifier: MIT */
/*!
 * \file quo_mod.c
 * \brief Quotient and modulo function implementations.
 * \details Implements the quotient and modulo function declared in
 * the \c quo_mod.h header file.
 * \copyright 2025, Roy Ratcliffe, Northumberland, United Kingdom
 */

#include "quo_mod.h"

struct quo_mod quo_mod(int x, int y) {
  /*
   * Compute modulus using C's % operator. Note that C's % operator will yield
   * negative results when the numerator is negative.
   */
  int mod = x % y;

  /* Adjust negative modulus to be positive. Ensures that:
   *
   *    0 <= mod < y    when y > 0
   *    y < mod <= 0    when y < 0
   *
   * This matches Lua's modulo operator behaviour.
   */
  if (mod != 0 && (mod ^ y) < 0) {
    mod += y;
  }

  /*
   * Returns a quo_mod structure by casting an initialiser. Is this portable?
   */
  return (struct quo_mod){.quo = (x - mod) / y, .mod = mod};
}
