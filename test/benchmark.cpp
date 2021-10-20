#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "dict_order.h"

#include <sys/time.h>

using namespace testing;

#define WARMUP 20
#define ROUND 100

TEST(DictOrderBaseline, fixed) {
  DictOrderBaseline order;

  std::vector<uint32_t> pattern;
  int idx;
  std::vector<uint32_t> expect;
  std::vector<uint32_t> result;

  pattern = {8, 1, 2, 3, 7, 4, 5, 6};
  idx = 2015;
  expect = {8, 3, 6, 7, 4, 5, 2, 1};
  EXPECT_TRUE(order.perm(result, pattern, idx));
  EXPECT_THAT(result, ElementsAreArray(expect));

  for (int i = 0; i < WARMUP; ++i) {
    order.perm(result, pattern, idx);
  }
  
  timeval s, e;
  gettimeofday(&s, NULL);
  for (int i = 0; i < ROUND; ++i) {
    order.perm(result, pattern, idx);
  }
  gettimeofday(&e, NULL);
  double time_ms = 1000.0 * (e.tv_sec - s.tv_sec) + (e.tv_usec - s.tv_usec) / 1000.0;
  dbg(time_ms / ROUND);
}