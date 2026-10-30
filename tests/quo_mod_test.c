#include "quo_mod.h"

#include <limits.h>
/* Keep assert-based tests enabled in Release builds. */
#ifdef NDEBUG
#undef NDEBUG
#endif
#include <assert.h>
#include <math.h>
#include <stdlib.h>

/*
 * Cross-check modulo results against Lua-style floor-based modulo:
 *
 *    #define luai_nummod(a, b) ((a) - floor((double)(a) / (b)) * (b))
 *
 * A nonzero result has the divisor's sign. Use this floating-point reference
 * only for the small integer range below, where rounding does not affect it.
 */
#define luai_nummod(a, b) ((a) - floor((double)(a) / (b)) * (b))

static double nummod(double x, double y) { return luai_nummod(x, y); }

static void check_quo_mod(int x, int y) {
  const long long trunc_quo = (long long)x / y;
  const long long trunc_mod = (long long)x % y;
  long long expected_quo = trunc_quo;
  long long expected_mod = trunc_mod;

  if (expected_mod != 0 && (expected_mod < 0) != (y < 0)) {
    expected_mod += y;
    expected_quo--;
  }

  const struct quo_mod qm = quo_mod(x, y);
  assert(qm.quo == expected_quo);
  assert(qm.mod == expected_mod);
  assert((long long)x == (long long)y * qm.quo + qm.mod);
  if (y > 0)
    assert(0 <= qm.mod && qm.mod < y);
  else
    assert(y < qm.mod && qm.mod <= 0);
}

int quo_mod_test(int argc, char **argv) {
  static const int boundary_values[] = {
      INT_MIN, INT_MIN + 1, -2, -1, 0, 1, 2, INT_MAX - 1, INT_MAX,
  };
  static const struct {
    int x, y, quo, mod;
  } cases[] = {
      {7, 3, 2, 1},
      {-7, 3, -3, 2},
      {7, -3, -3, -2},
      {-7, -3, 2, -1},
      {6, -3, -2, 0},
      {0, INT_MIN, 0, 0},
      {INT_MIN, 3, INT_MIN / 3 - (INT_MIN % 3 != 0),
       INT_MIN % 3 + (INT_MIN % 3 != 0 ? 3 : 0)},
      {INT_MIN, -3, INT_MIN / -3, INT_MIN % -3},
      {INT_MAX, -3, INT_MAX / -3 - (INT_MAX % -3 != 0),
       INT_MAX % -3 - (INT_MAX % -3 != 0 ? 3 : 0)},
      {INT_MAX, INT_MIN, -1, -1},
      {INT_MIN, INT_MIN, 1, 0},
      {INT_MIN, INT_MAX,
       INT_MIN / INT_MAX - (INT_MIN % INT_MAX != 0),
       INT_MIN % INT_MAX + (INT_MIN % INT_MAX != 0 ? INT_MAX : 0)},
  };

  for (size_t i = 0; i < sizeof cases / sizeof cases[0]; i++) {
    const int x = cases[i].x;
    const int y = cases[i].y;
    const struct quo_mod qm = quo_mod(x, y);
    assert(qm.quo == cases[i].quo);
    assert(qm.mod == cases[i].mod);
    assert((long long)x == (long long)y * qm.quo + qm.mod);
    if (y > 0)
      assert(0 <= qm.mod && qm.mod < y);
    else
      assert(y < qm.mod && qm.mod <= 0);
  }

  /*
   * Exercise every valid pairing of the listed boundary values, excluding zero
   * denominators and INT_MIN / -1. Compute expected results in long long to avoid
   * overflowing intermediate int arithmetic.
   */
  for (size_t i = 0; i < sizeof boundary_values / sizeof boundary_values[0];
       i++)
    for (size_t j = 0; j < sizeof boundary_values / sizeof boundary_values[0];
         j++) {
      const int x = boundary_values[i];
      const int y = boundary_values[j];
      if (y == 0 || (x == INT_MIN && y == -1))
        continue;
      check_quo_mod(x, y);
    }

  /*
   * Exhaustively check every pair in [-333, 333], excluding zero denominators.
   * Verify the quotient, remainder, x = y * quo + mod invariant, and remainder
   * bounds against the integer oracle; cross-check Lua-style modulo as well.
   */
  for (int x = -333; x <= 333; x++)
    for (int y = -333; y <= 333; y++) {
      if (y == 0)
        continue;
      check_quo_mod(x, y);
      assert(nummod(x, y) == quo_mod(x, y).mod);
    }

  return EXIT_SUCCESS;
}
