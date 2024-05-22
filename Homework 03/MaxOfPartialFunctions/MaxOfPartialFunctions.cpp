#include "MaxOfPartialFunctions.h"
#include <algorithm>
#include <limits>

MaxOfPartialFunctions::MaxOfPartialFunctions(const PartialFunction** functions, int16_t count)
    : PartialFunctionOperation(functions, count) {}

MaxOfPartialFunctions::MaxOfPartialFunctions(PartialFunction**&& functions, int16_t count)
    : PartialFunctionOperation(std::move(functions), count) {}

PartialFunction* MaxOfPartialFunctions::clone() const
{
    return new MaxOfPartialFunctions(*this);
}

bool MaxOfPartialFunctions::isDefinedAt(int32_t x) const 
{
    for (int16_t i = 0; i < count; ++i) 
    {
        if (!functions[i]->isDefinedAt(x))
            return false;
    }
    return true;
}

int32_t MaxOfPartialFunctions::calculate(int32_t x) const
{
    int32_t maxVal = INT32_MIN;
    bool defined = true;

    for (int16_t i = 0; i < count; ++i)
    {
        if (!functions[i]->isDefinedAt(x))
        {
            defined = false;
            break;
        }
        maxVal = std::max(maxVal, functions[i]->calculate(x));
    }

    if (!defined)
        throw std::runtime_error("Function not defined at this point");

    return maxVal;
}
