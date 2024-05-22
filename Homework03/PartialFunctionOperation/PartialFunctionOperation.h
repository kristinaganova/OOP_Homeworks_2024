#pragma once
#include "PartialFunction.h"

class PartialFunctionOperation : public PartialFunction
{
private:
	void copyFrom(const PartialFunctionOperation& other);
	void free();
	void moveFrom(PartialFunctionOperation&& other);
public:
	PartialFunctionOperation(const PartialFunction** PartialFunctions, int16_t count);
	PartialFunctionOperation(PartialFunction**&& PartialFunctions, int16_t count);

	PartialFunctionOperation(const PartialFunctionOperation& other);
	PartialFunctionOperation& operator=(const PartialFunctionOperation& other);

	PartialFunctionOperation(PartialFunctionOperation&& other) noexcept;
	PartialFunctionOperation& operator=(PartialFunctionOperation&& other) noexcept;

	~PartialFunctionOperation();
protected:
	PartialFunction** functions;
	int16_t count;
};