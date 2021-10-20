#ifndef SJT_ORDER_H
#define SJT_ORDER_H

#include <algorithm>

#include "perm_base.h"

#define LEFT false
#define RIGHT true

class SJTOrderBaseline: public Perm {
public:
  virtual bool perm(std::vector<uint32_t>& result, const std::vector<uint32_t>& pattern, int idx);
};


#endif