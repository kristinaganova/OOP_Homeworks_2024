#pragma once
#include <cstdint>
#include "Vector.hpp"
#include "Pair.hpp"

class BaseCriteria 
{
protected:
    Vector<int32_t> numbers;
public:
    BaseCriteria(const Vector<int32_t>& numbers);
    virtual Pair<bool, int32_t> operator()(int32_t x) const = 0;
    virtual ~BaseCriteria() = default;
};