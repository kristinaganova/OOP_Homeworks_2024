#pragma once
#include <iostream>
class PartialFunction
{
public:
	virtual PartialFunction* clone() const = 0;
	virtual ~PartialFunction() = default;
	virtual bool isDefinedAt(int32_t x) const = 0;
	virtual int32_t calculate(int32_t x) const = 0;
};