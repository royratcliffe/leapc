/* SPDX-License-Identifier: MIT */
/*!
 * \file quo_mod.c
 * \brief Quotient and modulus function implementations.
 * \copyright 2025, Roy Ratcliffe, Northumberland, United Kingdom
 */
#include "quo_mod.h"

struct quo_mod quo_mod(int x, int y) {
  int mod = x % y;
  /*
   * Returns a quo_mod structure by casting an initialiser. Is this portable?
   */
  return (struct quo_mod){.quo = (x - mod) / y, .mod = mod};
}
