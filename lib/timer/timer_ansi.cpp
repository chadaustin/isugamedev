#include <time.h>
#include "timer.hpp"


u64 GetNow() {
  return u64(1000000) * clock() / CLOCKS_PER_SEC;
}
