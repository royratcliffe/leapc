#include "quo_mod.h"

struct quo_mod quo_mod(int x, int y) {
  int mod = x % y;
  return (struct quo_mod){(x - mod) / y, mod};
}
