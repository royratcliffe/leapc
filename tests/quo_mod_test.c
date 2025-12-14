#include "quo_mod.h"

#include <assert.h>

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
