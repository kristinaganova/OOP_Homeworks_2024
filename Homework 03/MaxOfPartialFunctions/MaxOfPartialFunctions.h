#pragma once
#include "PartialFunctionOperation.h"

class MaxOfPartialFunctions : public PartialFunctionOperation
{
public:
	MaxOfPartialFunctions(const PartialFunction** functions, int16_t count);
	MaxOfPartialFunctions(PartialFunction**&& functions, int16_t count);

	PartialFunction* clone() const override;
	bool isDefinedAt(int32_t x) const override;
	int32_t calculate(int32_t x) const override;
};