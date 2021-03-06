#include <time.h>
#include <sys/time.h>
#include "timer.hpp"


u64 GetNow() {
  // use the POSIX realtime clock to get the current time
  struct timespec tp;
  int result = clock_gettime(CLOCK_REALTIME, &tp);
  if (result == 0) {
    return u64(tp.tv_sec) * 1000000 + u64(tv.nsec) / 1000;
  } else {
    // can't use realtime clock!  Try to use gettimeofday
    struct timeval tv;
    gettimeofday(&tv, 0);
    return u64(tv.tv_sec) * 1000000 + tv.tv_usec;
  }
}
