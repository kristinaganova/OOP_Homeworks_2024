#pragma once
#include "PartialFunctionOperation.h"

class MinOfPartialFunctions : public PartialFunctionOperation
{
public:
	MinOfPartialFunctions(const PartialFunction** functions, int16_t count);
	MinOfPartialFunctions(PartialFunction**&& functions, int16_t count);

	PartialFunction* clone() const override;
	bool isDefinedAt(int32_t x) const override;
	int32_t calculate(int32_t x) const override;
};