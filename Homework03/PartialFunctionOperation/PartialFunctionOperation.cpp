#include "PartialFunctionOperation.h"

void PartialFunctionOperation::copyFrom(const PartialFunctionOperation& other)
{
	count = other.count;
	functions = new PartialFunction*[count];
	for (int16_t i = 0; i < count; i++)
		functions[i] = other.functions[i]->clone();
}

void PartialFunctionOperation::free()
{
	for (int16_t i = 0; i < count; i++)
		delete functions[i];
	delete[] functions;
}

void PartialFunctionOperation::moveFrom(PartialFunctionOperation&& other)
{
	functions = other.functions;
	count = other.count;

	other.functions = nullptr;
	other.count = 0;
}

PartialFunctionOperation::PartialFunctionOperation(const PartialFunction** partialFunctions, int16_t count)
{
	this->functions = new PartialFunction*[count];
	for (int16_t i = 0; i < count; i++)
		this->functions[i] = partialFunctions[i]->clone();
}

PartialFunctionOperation::PartialFunctionOperation(PartialFunction**&& partialFunctions, int16_t count)
{
	this->functions = partialFunctions;
	this->count = count;
	partialFunctions = nullptr;
}

PartialFunctionOperation::PartialFunctionOperation(const PartialFunctionOperation& other)
{
	copyFrom(other);
}

PartialFunctionOperation& PartialFunctionOperation::operator=(const PartialFunctionOperation& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

PartialFunctionOperation::PartialFunctionOperation(PartialFunctionOperation&& other) noexcept
{
	moveFrom(std::move(other));
}

PartialFunctionOperation& PartialFunctionOperation::operator=(PartialFunctionOperation&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

PartialFunctionOperation::~PartialFunctionOperation()
{
	free();
}