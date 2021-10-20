#include "ascend_order.h"

bool AscendOrderBaseline::perm(std::vector<uint32_t>& result, const std::vector<uint32_t>& pattern, int idx) {
  //dbg(pattern, idx);
  int num = pattern.size();  
  result.resize(num);
  if (num == 0) return false;
  if (idx == 0 || num <= 1) {
    for (int i = 0; i < num; ++i) result[i] = pattern[i];
    return true;
  }

  std::vector<int> pattern_inter(num - 1, 0);
  std::vector<int> idx_inter(num - 1, 0);
  for (int i = num - 2, k = 0; i >= 0; i--, k++) {
    int t = 0;
    for (int j = num - 1; int(pattern[j]) != num - i; --j) {
      if (int(pattern[j]) < num - i) t++;
    }
    pattern_inter[k] = t;
  }
  //dbg(pattern_inter);
  for (int i = 0, base = 2, n = idx; n != 0; ++base, ++i) {
    idx_inter[i] = n % base;
    n /= base;
  }
  //dbg(idx_inter);

  // add
  int carry = 0;
  for (int i = 0, base = 2; i < num - 1; ++i, ++base) {
    pattern_inter[i] += idx_inter[i] + carry;
    carry = pattern_inter[i] / base;
    pattern_inter[i] %= base;
    if (pattern_inter[i] < 0) {
      pattern_inter[i] += base;
      carry -= 1;
    }
    //dbg(carry);
  }
  if (carry != 0) return false;
  //dbg(pattern_inter);

  // generate new pattern
  std::fill(result.begin(), result.end(), 1);
  for (int i = num - 2, k = num; i >= 0; --i, --k) {
    int space_num = pattern_inter[i];
    int pos = num - 1;
    //dbg(space_num);
    while (space_num > 0 || result[pos] != 1) {
      if (result[pos] == 1) space_num--;
      pos--;
    }
    result[pos] = k;
    //dbg(k, pos, result);
  }

  //dbg(result);
  return true;
}