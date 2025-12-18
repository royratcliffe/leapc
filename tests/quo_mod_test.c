#include "quo_mod.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>

#define luai_nummod(a, b) ((a) - floor((double)(a) / (b)) * (b))

static double nummod(double x, double y) { return luai_nummod(x, y); }

int quo_mod_test(int argc, char **argv) {
  for (int x = -333; x <= 333; x++)
    for (int y = -333; y <= 333; y++) {
      if (y == 0)
        continue;
      struct quo_mod qm = quo_mod(x, y);
      assert(x == (y * qm.quo + qm.mod));
    }
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
  return 0;
}
