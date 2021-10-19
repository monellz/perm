#ifndef DICT_ORDER_H
#define DICT_ORDER_H

#include <algorithm>

#include "perm_base.h"


class DictOrderBaseline: public Perm {
public:
  virtual std::vector<uint32_t> perm(const std::vector<uint32_t>& base, int idx);
};

#endif