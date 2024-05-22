#include "MinOfPartialFunctions.h"
#include <algorithm>
#include <limits>

MinOfPartialFunctions::MinOfPartialFunctions(const PartialFunction** functions, int16_t count)
    : PartialFunctionOperation(functions, count) {}

MinOfPartialFunctions::MinOfPartialFunctions(PartialFunction**&& functions, int16_t count)
    : PartialFunctionOperation(std::move(functions), count) {}

PartialFunction* MinOfPartialFunctions::clone() const 
{
    return new MinOfPartialFunctions(*this);
}

bool MinOfPartialFunctions::isDefinedAt(int32_t x) const
{
    for (int16_t i = 0; i < count; ++i) 
    {
        if (!functions[i]->isDefinedAt(x)) 
            return false;
    }
    return true;
}

int32_t MinOfPartialFunctions::calculate(int32_t x) const 
{
    int32_t minVal = INT32_MAX;
    bool defined = true;

    for (int16_t i = 0; i < count; ++i)
    {
        if (!functions[i]->isDefinedAt(x)) 
        {
            defined = false;
            break;
        }
        minVal = std::min(minVal, functions[i]->calculate(x));
    }

    if (!defined)
        throw std::runtime_error("Function not defined at this point");

    return minVal;
}