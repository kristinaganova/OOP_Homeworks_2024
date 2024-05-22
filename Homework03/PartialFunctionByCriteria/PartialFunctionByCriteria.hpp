#pragma once
#include "PartialFunction.h"

template<class T>
class PartialFunctionByCriteria : public PartialFunction
{
	T criteria;
public:
	PartialFunctionByCriteria(const T& criteria);
	PartialFunctionByCriteria(T&& criteria);
	PartialFunction* clone() const override;
	bool isDefinedAt(int32_t x) const override;
	int32_t calculate(int32_t x) const override;
};

template<class T>
PartialFunctionByCriteria<T>::PartialFunctionByCriteria(const T& criteria) : criteria(criteria) {}

template<class T>
PartialFunctionByCriteria<T>::PartialFunctionByCriteria(T&& criteria) : criteria(std::move(criteria)) {}

template<class T>
PartialFunction* PartialFunctionByCriteria<T>::clone() const
{
	return new PartialFunctionByCriteria<T>(*this);
}

template<class T>
bool PartialFunctionByCriteria<T>::isDefinedAt(int32_t x) const
{
	return criteria(x).getFirst();
}

template<class T>
int32_t PartialFunctionByCriteria<T>::calculate(int32_t x) const
{
	return criteria(x).getSecond();
}
