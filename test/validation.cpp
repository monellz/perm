#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "dict_order.h"

using namespace testing;

TEST(DictOrderBaseline, simple) {
  DictOrderBaseline order;

  std::vector<uint32_t> base;
  std::vector<uint32_t> expect;

  base = {8, 1, 2, 3, 7, 4, 5, 6};
  expect = {8, 3, 6, 7, 4, 5, 2, 1};
  auto&& r = order.perm(base, 2015);
  EXPECT_THAT(r, ElementsAreArray(expect));
}
