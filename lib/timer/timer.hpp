/**
 * Platform-independent abstraction for high-resolution timers.
 */


#ifndef TIMER_HPP
#define TIMER_HPP


#ifdef _MSC_VER                  // VC++
typedef unsigned __int64   u64;
#else                            // assume gcc
typedef unsigned long long u64;
#endif


/**
 * Return current time in microseconds.
 */
u64 GetNow();


#endif
