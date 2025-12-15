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
  const int mod = x % y;
  /*
   * Returns a quo_mod structure by casting an initialiser. Is this portable?
   */
  return (struct quo_mod){.quo = (x - mod) / y, .mod = mod};
}
