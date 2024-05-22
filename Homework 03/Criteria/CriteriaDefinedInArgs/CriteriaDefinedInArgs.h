#pragma once
#include "BaseCriteria.h"

class CriteriaDefinedInArgs : public BaseCriteria 
{
    Vector<int32_t> results;
public:
    CriteriaDefinedInArgs(const Vector<int32_t>& numbers, const Vector<int32_t>& results);
    Pair<bool, int32_t> operator()(int32_t x) const override;
};