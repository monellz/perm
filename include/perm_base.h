#ifndef PERM_BASE_H
#define PERM_BASE_H

#include <cstdint>
#include <vector>

#include "util.h"

class Perm {
public:
  virtual std::vector<uint32_t> perm(const std::vector<uint32_t>& base, int idx) = 0;
  virtual ~Perm() {}
};

#endif