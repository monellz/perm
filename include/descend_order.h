#ifndef DESCEND_ORDER_H
#define DESCEND_ORDER_H

#include <algorithm>

#include "perm_base.h"

class DescendOrderBaseline: public Perm {
public:
  virtual bool perm(std::vector<uint32_t>& result, const std::vector<uint32_t>& pattern, int idx);
};


#endif