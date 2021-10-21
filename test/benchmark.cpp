#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "dict_order.h"

#include <sys/time.h>

using namespace testing;

#define WARMUP 2
#define ROUND 8

timeval t0, t1;
#define timestamp(t) gettimeofday(&t, NULL)
#define get_duration(s, e) (1000.0 * (e.tv_sec - s.tv_sec) + (e.tv_usec - s.tv_usec) / 1000.0)

TEST(DictOrder, fixed) {
  DictOrderBaseline baseline;
  DictOrder order;

  std::vector<uint32_t> pattern;
  int idx;
  std::vector<uint32_t> expect;
  std::vector<uint32_t> baseline_result;
  std::vector<uint32_t> result;

  int num = 10000;
  for (int i = 0; i < num; ++i) pattern.push_back(i + 1);
  result.resize(num);
  baseline_result.resize(num);
  idx = 1000;

  for (int i = 0; i < WARMUP; ++i) {
    baseline.perm(baseline_result, pattern, idx);
  }
  timestamp(t0);
  for (int i = 0; i < ROUND; ++i) {
    baseline.perm(baseline_result, pattern, idx);
  }
  timestamp(t1);
  double dictorder_baseline_ms = get_duration(t0, t1);
  dbg(dictorder_baseline_ms / ROUND);


  for (int i = 0; i < WARMUP; ++i) {
    order.perm(result, pattern, idx);
  }
  timestamp(t0);
  for (int i = 0; i < ROUND; ++i) {
    order.perm(result, pattern, idx);
  }
  timestamp(t1);
  double dictorder_ms = get_duration(t0, t1);
  dbg(dictorder_ms / ROUND);

  double speedup = dictorder_baseline_ms / dictorder_ms;
  dbg(speedup);
  EXPECT_THAT(result, ElementsAreArray(baseline_result));
}