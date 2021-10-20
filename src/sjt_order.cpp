#include "sjt_order.h"

bool SJTOrderBaseline::perm(std::vector<uint32_t>& result, const std::vector<uint32_t>& pattern, int idx) {
  //dbg(pattern, idx);
  int num = pattern.size();  
  result.resize(num);
  if (num == 0) return false;
  if (idx == 0 || num <= 1) {
    for (int i = 0; i < num; ++i) result[i] = pattern[i];
    return true;
  }


  std::vector<int> idx_map(num);
  for (int i = 0; i < num; ++i) {
    idx_map[pattern[i] - 1] = i;
  }
  //dbg(idx_map);

  std::vector<int> pattern_inter(num - 1, 0);
  std::vector<int> idx_inter(num - 1, 0);
  // direction
  // 1/2 is always left
  std::vector<bool> direction(num, LEFT);
  // set b2
  pattern_inter.back() = 0;
  for (int j = idx_map[2 - 1] + 1; j < num; ++j) {
    if (pattern[j] < 2) pattern_inter.back()++;
  }
  for (int i = num - 3; i >= 0; --i) {
    int ti = num - i;
    int ti_idx = idx_map[ti - 1];
    // from b3 ..
    if (ti % 2 == 0) {
      // even
      direction[ti_idx] = (pattern_inter[i + 2] + pattern_inter[i + 1]) % 2 == 0? LEFT: RIGHT;
    } else {
      // odd
      direction[ti_idx] = pattern_inter[i + 1] % 2 == 0? LEFT: RIGHT;
    }

    int ti_num = 0;
    if (direction[ti_idx] == LEFT) {
      for (int j = ti_idx + 1; j < num; ++j) {
        if (int(pattern[j]) < ti) ti_num++;
      }
    } else {
      for (int j = ti_idx - 1; j >= 0; --j) {
        if (int(pattern[j]) < ti) ti_num++;
      }
    }
    pattern_inter[i] = ti_num;
  }

  //dbg(direction);
  //dbg(pattern_inter);


  for (int i = 0, base = num, n = idx; n != 0; --base, ++i) {
    idx_inter[i] = n % base;
    n /= base;
  }
  //dbg(idx_inter);

  // add
  int carry = 0;
  for (int i = 0, base = num; i < num - 1; ++i, --base) {
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
  for (int i = 0, k = num; i < num - 2; ++i, --k) {
    int space_num = pattern_inter[i];
    bool dir;
    if (k % 2 == 0) {
      // even
      dir = (pattern_inter[i + 1] + pattern_inter[i + 2]) % 2 == 0? LEFT: RIGHT;
    } else {
      // odd
      dir = pattern_inter[i + 1] % 2 == 0? LEFT: RIGHT;
    }

    if (dir == LEFT) {
      int pos = num - 1;
      //dbg(space_num);
      while (space_num > 0 || result[pos] != 1) {
        if (result[pos] == 1) space_num--;
        pos--;
      }
      result[pos] = k;
      //dbg("left", k, pos, result);
    } else {
      int pos = 0;
      //dbg(space_num);
      while (space_num > 0 || result[pos] != 1) {
        if (result[pos] == 1) space_num--;
        pos++;
      }
      result[pos] = k;
      //dbg("right", k, pos, result);
    }
  }

  {
    int pos = num - 1;
    int space_num = pattern_inter.back();
    while (space_num > 0 || result[pos] != 1) {
      if (result[pos] == 1) space_num--;
      pos--;
    }
    result[pos] = 2;
  }

  //dbg(result);
  return true;
}