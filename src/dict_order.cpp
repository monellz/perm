#include "dict_order.h"

std::vector<uint32_t> DictOrderBaseline::perm(const std::vector<uint32_t>& pattern, int idx) {
  std::vector<uint32_t> new_pattern(pattern.size());
  dbg(pattern, idx);
  if (idx == 0 || pattern.size() <= 1) return new_pattern;

  static uint32_t pattern_inter[1024];
  static uint32_t idx_inter[1024];
  int pattern_inter_size = 0, idx_inter_size = 0;

  for (int i = pattern.size() - 2; i >= 0; i--) {
    int t = 0;
    for (int j = i + 1; j < pattern.size(); ++j) {
      if (pattern[j] < pattern[i]) t++;
    }
    pattern_inter[pattern_inter_size++] = t;
  }
  dbg(std::vector<uint32_t>(pattern_inter, pattern_inter + pattern_inter_size));
  // cantor expansion
  for (int i = 2, n = idx; n != 0; ++i) {
    idx_inter[idx_inter_size++] = n % i;
    n /= i;
  }
  dbg(std::vector<uint32_t>(idx_inter, idx_inter + idx_inter_size));

  // padding
  int size = max(pattern_inter_size, idx_inter_size);
  // 是否会进位？ proof
  for (int i = pattern_inter_size; i < size; ++i) pattern_inter[i] = 0;
  for (int i = idx_inter_size; i < size; ++i) idx_inter[i] = 0;
  dbg(size);

  // add
  for (int i = 0, base = 2, carry = 0; i < size; ++i) {
    pattern_inter[i] += idx_inter[i] + carry;
    carry = pattern_inter[i] / base;
    pattern_inter[i] %= base;
    base++;
  }
  dbg(std::vector<uint32_t>(pattern_inter, pattern_inter + size));

  // generate new pattern
  std::vector<uint32_t> tmp(pattern.size());
  for (int i = 0; i < tmp.size(); ++i) {
    tmp[i] = i + 1;
  }
  dbg(tmp);

  for (int i = 0; i < new_pattern.size(); ++i) {
    new_pattern[i] = tmp[pattern_inter[size - 1]];
    tmp.erase(tmp.begin() + pattern_inter[size - 1]);
    std::sort(tmp.begin(), tmp.end());
    size--;
  }
  dbg(new_pattern);

  return new_pattern;
}