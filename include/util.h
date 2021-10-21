#ifndef UTIL_H
#define UTIL_H

#define DBG_MACRO_NO_WARNING
#include "dbg/dbg.h"

#include <cassert>
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)<(b))?(b):(a))


// binary indexed tree
#define BIT_LOWBIT(x) ((x) & (-(x)))
#define BIT_UPDATE(arr, num, idx, k)    \
  do {                                  \
    int x = idx;                        \
    while (x <= num) {                  \
      arr[x] += k;                      \
      x += BIT_LOWBIT(x);               \
    }                                   \
  } while (0)

#define BIT_QUERY(arr, num, idx, res)   \
  do {                                  \
    int x = idx;                        \
    res = 0;                            \
    while (x >= 1) {                    \
      res += arr[x];                    \
      x -= BIT_LOWBIT(x);               \
    }                                   \
  } while (0)                           
#endif