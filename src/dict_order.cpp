#include "dict_order.h"

static __attribute__((unused)) std::vector<uint32_t> inter(int n) {
  std::vector<uint32_t> r;
  for (int i = 2; n != 0; ++i) {
    r.push_back(n % i);
    n /= i;
  }
  return r;
}

bool DictOrderBaseline::perm(std::vector<uint32_t>& result, const std::vector<uint32_t>& pattern, int idx) {
  // dbg(pattern, idx);
  int num = pattern.size();
  result.resize(num);
  if (num == 0 || num > this->MAX_NUM) return false;
  if (idx == 0 || num <= 1) {
    for (int i = 0; i < num; ++i) result[i] = pattern[i];
    return true;
  }

  uint32_t pattern_cantor = 0;
  for (int i = num - 2, k = 1; i >= 0; i--, k++) {
    int t = 0;
    for (int j = i + 1; j < num; ++j) {
      if (pattern[j] < pattern[i]) t++;
    }
    pattern_cantor += FACTORIAL[k] * t;
  }
  // dbg(inter(pattern_cantor));
  int result_cantor = pattern_cantor + idx;
  // dbg(inter(result_cantor));

  // generate new pattern
  std::vector<uint32_t> tmp(num);
  for (int i = 0; i < num; ++i) {
    tmp[i] = i + 1;
  }
  // dbg(tmp);
  for (int base = num - 1, n = result_cantor, i = 0; base >= 0; --base, ++i) {
    int t = n / FACTORIAL[base];
    n %= FACTORIAL[base];
    result[i] = tmp[t];
    tmp.erase(tmp.begin() + t);
    std::sort(tmp.begin(), tmp.end());
  } 
  // dbg(result);
  return true;
}