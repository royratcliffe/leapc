#include "quo_mod.h"

#include <limits.h>
/* Keep assert-based tests enabled in Release builds. */
#ifdef NDEBUG
#undef NDEBUG
#endif
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define luai_nummod(a, b) ((a) - floor((double)(a) / (b)) * (b))

static double nummod(double x, double y) { return luai_nummod(x, y); }

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
   * Exercise every numerator/denominator pairing near the int limits. Compute
   * expected results in long long so intermediate values cannot overflow.
   */
  for (size_t i = 0; i < sizeof boundary_values / sizeof boundary_values[0];
       i++)
    for (size_t j = 0; j < sizeof boundary_values / sizeof boundary_values[0];
         j++) {
      const int x = boundary_values[i];
      const int y = boundary_values[j];
      if (y == 0 || (x == INT_MIN && y == -1))
        continue;

      long long quo = (long long)x / y;
      long long mod = (long long)x % y;
      if (mod != 0 && (mod < 0) != (y < 0)) {
        mod += y;
        quo--;
      }

      const struct quo_mod qm = quo_mod(x, y);
      assert(qm.quo == quo);
      assert(qm.mod == mod);
    }

  /*
   * Verify that x = y * quo + mod invariant holds for all combinations of x and
   * y in some reasonable range.
   */
  for (int x = -333; x <= 333; x++)
    for (int y = -333; y <= 333; y++) {
      if (y == 0)
        continue;
      struct quo_mod qm = quo_mod(x, y);
      assert(x == (y * qm.quo + qm.mod));
    }

  /*
   * Cross-check modulo results against Lua's nummod() function. Lua's modulo
   * function is defined in lmathlib.c as:
   *
   *    #define luai_nummod(a, b) ((a) - floor((double)(a) / (b)) * (b))
   *
   * This definition ensures that the result of the modulo operation has the
   * same sign as the divisor (b), which is a common convention in programming
   * languages.
   */
  for (int x = -333; x <= 333; x++)
    for (int y = -333; y <= 333; y++) {
      if (y == 0)
        continue;
      struct quo_mod qm = quo_mod(x, y);
      double lua_mod = nummod(x, y);
      if (lua_mod != qm.mod) {
        (void)printf("Discrepancy for x=%d, y=%d: lua_mod=%f, qm.mod=%d\n", x, y, lua_mod, qm.mod);
      }
      assert(lua_mod == qm.mod);
    }

  return EXIT_SUCCESS;
}
