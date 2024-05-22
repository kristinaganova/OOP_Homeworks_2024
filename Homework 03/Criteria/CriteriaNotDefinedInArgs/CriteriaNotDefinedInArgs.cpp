#include "CriteriaNotDefinedInArgs.h"

CriteriaNotDefinedInArgs::CriteriaNotDefinedInArgs(const Vector<int32_t>& numbers) : BaseCriteria(numbers) {}

Pair<bool, int32_t> CriteriaNotDefinedInArgs::operator()(int32_t x) const 
{
    size_t size = numbers.getSize();
    for (size_t i = 0; i < size; ++i)
    {
        if (numbers[i] == x) 
            return Pair<bool, int32_t>(false, 0);
    }
    return Pair<bool, int32_t>(true, x);
}