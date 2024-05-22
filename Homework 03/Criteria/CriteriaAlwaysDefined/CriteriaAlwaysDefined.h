#pragma once
#include "BaseCriteria.h"

class CriteriaAlwaysDefined : public BaseCriteria
{
public:
    CriteriaAlwaysDefined(const Vector<int32_t>& numbers);
    Pair<bool, int32_t> operator()(int32_t x) const override;
};
