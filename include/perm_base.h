#ifndef PERM_BASE_H
#define PERM_BASE_H

#include <cstdint>
#include <cstdlib>
#include <vector>

#include "util.h"

static uint32_t FACTORIAL[] __attribute__((unused)) = {
  1,
  1,
  2,
  6,
  24,
  120,
  720,
  5040,
  40320,
  362880,
  3628800,
  39916800,
  479001600
};

class Perm {
public:
  virtual bool perm(std::vector<uint32_t>& result, const std::vector<uint32_t>& pattern, int idx) = 0;
  virtual ~Perm() {}
protected:
  static const int MAX_NUM = 10;
};

#endif