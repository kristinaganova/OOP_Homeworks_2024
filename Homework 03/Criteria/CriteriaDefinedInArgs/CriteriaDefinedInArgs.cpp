#include "CriteriaDefinedInArgs.h"
#include <iostream>

CriteriaDefinedInArgs::CriteriaDefinedInArgs(const Vector<int32_t>& numbers, const Vector<int32_t>& results) : BaseCriteria(numbers), results(results) {}

Pair<bool, int32_t> CriteriaDefinedInArgs::operator()(int32_t x) const
{
    size_t size = numbers.getSize();
    for (size_t i = 0; i < size; ++i)
    {
        if (numbers[i] == x)
            return Pair<bool, int32_t>(true, results[i]);
    }
    return Pair<bool, int32_t>(false, 0);
}