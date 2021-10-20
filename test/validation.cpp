#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "dict_order.h"

using namespace testing;

TEST(DictOrderBaseline, simple) {
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

  pattern = {8, 3, 6, 7, 4, 5, 2, 1};
  idx = -2015;
  expect = {8, 1, 2, 3, 7, 4, 5, 6};
  EXPECT_TRUE(order.perm(result, pattern, idx));
  EXPECT_THAT(result, ElementsAreArray(expect));
}
