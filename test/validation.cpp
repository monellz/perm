#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "dict_order.h"
#include "ascend_order.h"
#include "descend_order.h"
#include "sjt_order.h"


using namespace testing;

TEST(DictOrderBaseline, simple) {
  DictOrderBaseline baseline;
  DictOrder order;

  std::vector<uint32_t> pattern;
  int idx;
  std::vector<uint32_t> expect;
  std::vector<uint32_t> result;

  pattern = {8, 1, 2, 3, 7, 4, 5, 6};
  idx = 2015;
  expect = {8, 3, 6, 7, 4, 5, 2, 1};
  EXPECT_TRUE(baseline.perm(result, pattern, idx));
  EXPECT_THAT(result, ElementsAreArray(expect));
  EXPECT_TRUE(order.perm(result, pattern, idx));
  EXPECT_THAT(result, ElementsAreArray(expect));

  pattern = {8, 3, 6, 7, 4, 5, 2, 1};
  idx = -2015;
  expect = {8, 1, 2, 3, 7, 4, 5, 6};
  EXPECT_TRUE(baseline.perm(result, pattern, idx));
  EXPECT_THAT(result, ElementsAreArray(expect));
  EXPECT_TRUE(order.perm(result, pattern, idx));
  EXPECT_THAT(result, ElementsAreArray(expect));

  pattern = {8, 3, 6, 7, 4, 5, 2, 1};
  idx = -2021;
  expect = {8, 1, 2, 3, 6, 4, 5, 7};
  EXPECT_TRUE(baseline.perm(result, pattern, idx));
  EXPECT_THAT(result, ElementsAreArray(expect));
  EXPECT_TRUE(order.perm(result, pattern, idx));
  EXPECT_THAT(result, ElementsAreArray(expect));
}

TEST(AscendOrderBaseline, simple) {
  AscendOrderBaseline order;

  std::vector<uint32_t> pattern;
  int idx;
  std::vector<uint32_t> expect;
  std::vector<uint32_t> result;

  pattern = {8, 6, 4, 5, 1, 2, 7, 3};
  idx = 2015;
  expect = {8, 3, 6, 7, 4, 5, 2, 1};
  EXPECT_TRUE(order.perm(result, pattern, idx));
  EXPECT_THAT(result, ElementsAreArray(expect));

  pattern = {8, 3, 6, 7, 4, 5, 2, 1};
  idx = -2015;
  expect = {8, 6, 4, 5, 1, 2, 7, 3};
  EXPECT_TRUE(order.perm(result, pattern, idx));
  EXPECT_THAT(result, ElementsAreArray(expect));

  pattern = {8, 3, 6, 7, 4, 5, 2, 1};
  idx = -2021;
  expect = {8, 6, 1, 5, 4, 2, 7, 3};
  EXPECT_TRUE(order.perm(result, pattern, idx));
  EXPECT_THAT(result, ElementsAreArray(expect));
}

TEST(DescendOrderBaseline, simple) {
  DescendOrderBaseline order;

  std::vector<uint32_t> pattern;
  int idx;
  std::vector<uint32_t> expect;
  std::vector<uint32_t> result;

  pattern = {3, 7, 6, 2, 4, 5, 1, 8};
  idx = 2015;
  expect = {8, 3, 6, 7, 4, 5, 2, 1};
  EXPECT_TRUE(order.perm(result, pattern, idx));
  EXPECT_THAT(result, ElementsAreArray(expect));

  pattern = {8, 3, 6, 7, 4, 5, 2, 1};
  idx = -2015;
  expect = {3, 7, 6, 2, 4, 5, 1, 8};
  EXPECT_TRUE(order.perm(result, pattern, idx));
  EXPECT_THAT(result, ElementsAreArray(expect));

  pattern = {8, 3, 6, 7, 4, 5, 2, 1};
  idx = -2021;
  expect = {3, 6, 7, 2, 4, 8, 5, 1};
  EXPECT_TRUE(order.perm(result, pattern, idx));
  EXPECT_THAT(result, ElementsAreArray(expect));
}

TEST(SJTOrderBaseline, simple) {
  SJTOrderBaseline order;

  std::vector<uint32_t> pattern;
  int idx;
  std::vector<uint32_t> expect;
  std::vector<uint32_t> result;

  pattern = {4, 8, 6, 7, 3, 2, 5, 1};
  idx = 2015;
  expect = {8, 3, 6, 7, 4, 5, 2, 1};
  EXPECT_TRUE(order.perm(result, pattern, idx));
  EXPECT_THAT(result, ElementsAreArray(expect));

  pattern = {8, 3, 6, 7, 4, 5, 2, 1};
  idx = -2015;
  expect = {4, 8, 6, 7, 3, 2, 5, 1};
  EXPECT_TRUE(order.perm(result, pattern, idx));
  EXPECT_THAT(result, ElementsAreArray(expect));

  pattern = {8, 3, 6, 7, 4, 5, 2, 1};
  idx = -2021;
  expect = {4, 7, 6, 3, 8, 2, 5, 1};
  EXPECT_TRUE(order.perm(result, pattern, idx));
  EXPECT_THAT(result, ElementsAreArray(expect));
}




TEST(All, badcase) {
  DictOrderBaseline dob;
  AscendOrderBaseline aob;
  DescendOrderBaseline deob;
  SJTOrderBaseline sjtob;
  
  std::vector<uint32_t> pattern;
  int idx;
  std::vector<uint32_t> result;

  pattern = {1, 2, 3, 4};
  idx = -1;
  EXPECT_FALSE(dob.perm(result, pattern, idx));
  EXPECT_FALSE(aob.perm(result, pattern, idx));
  EXPECT_FALSE(deob.perm(result, pattern, idx));
  EXPECT_FALSE(sjtob.perm(result, pattern, idx));

  pattern = {4, 3, 2, 1};
  idx = 20;
  EXPECT_FALSE(dob.perm(result, pattern, idx));
  EXPECT_FALSE(aob.perm(result, pattern, idx));
  EXPECT_FALSE(deob.perm(result, pattern, idx));
  EXPECT_FALSE(sjtob.perm(result, pattern, idx));
}