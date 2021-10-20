#ifndef DICT_ORDER_H
#define DICT_ORDER_H

#include <algorithm>

#include "perm_base.h"


class DictOrderBaseline: public Perm {
public:
  virtual bool perm(std::vector<uint32_t>& result, const std::vector<uint32_t>& pattern, int idx);
};

#endif