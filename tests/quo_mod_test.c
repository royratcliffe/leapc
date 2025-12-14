
#include <assert.h>

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
struct quo_mod quo_mod(int x, int y) {
  int mod = x % y;
  return (struct quo_mod){(x - mod) / y, mod};
}

int quo_mod_test(int argc, char **argv) {
  for (int x = -3; x <= 3; x++)
    for (int y = -3; y <= 3; y++) {
      if (y == 0)
        continue;
      struct quo_mod qm = quo_mod(x, y);
      assert(x == (y * qm.quo + qm.mod));
    }
  return 0;
}
