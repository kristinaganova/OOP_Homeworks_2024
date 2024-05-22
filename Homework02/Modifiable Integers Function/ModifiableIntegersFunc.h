#pragma once
#include "Vector.h"
#include "PairVector.h"
#include "Pair.h"
#include <cstdint>

struct Type
{
	char type : 2;

	bool isInjective() const
	{
		return (type & (1 << 0)) == 0;
	}

	bool isSurjective() const
	{
		return (type & (1 << 1)) == 0;
	}

	void setInjective()
	{
		type |= (1 << 0);
	}

	void setSurjective()
	{
		type |= (1 << 1);
	}
};

class ModifiableIntegersFunc
{
	bool isNotInExcludedPoints(int16_t point) const;
	void computeInjective();
	void computeSurjective();
	void computeResults();

public:
	ModifiableIntegersFunc(int16_t(*func)(int16_t));
	bool isInjective() const;
	bool isSurjective() const;
	bool isBijective() const;
	void inverse();
	void plot(int16_t x1, int16_t x2) const;
	void setCustomResults(int16_t input, int16_t result);
	void excludePoint(int16_t input);

	int16_t operator()(int16_t input) const;
	int16_t operator()(const ModifiableIntegersFunc& other, int16_t input) const;
	void operator+=(const ModifiableIntegersFunc& other);
	void operator-=(const ModifiableIntegersFunc& other);
	int16_t operator^(const Pair& pairOfKAndX) const; //because operator^ cannot have two parameters 

	void serialize(const char* filename) const;
	void serialize(std::ofstream& ofs) const;

	void deserialize(const char* filename);
	void deserialize(std::ifstream& ifs);

	friend bool operator<(const ModifiableIntegersFunc& lhs, const ModifiableIntegersFunc& rhs);
	friend bool operator<=(const ModifiableIntegersFunc& lhs, const ModifiableIntegersFunc& rhs);
	friend bool operator==(const ModifiableIntegersFunc& lhs, const ModifiableIntegersFunc& rhs);
	friend bool operator!=(const ModifiableIntegersFunc& lhs, const ModifiableIntegersFunc& rhs);
	friend bool operator>=(const ModifiableIntegersFunc& lhs, const ModifiableIntegersFunc& rhs);
	friend bool operator>(const ModifiableIntegersFunc& lhs, const ModifiableIntegersFunc& rhs);
	friend bool operator||(const ModifiableIntegersFunc& f1, const ModifiableIntegersFunc& f2);

private:
	Type type;
	int16_t(*func)(int16_t);
	Vector excludedPoints;
	PairVector customResults;
	PairVector results;
};
ModifiableIntegersFunc operator+(const ModifiableIntegersFunc& lhs, const ModifiableIntegersFunc& rhs);
ModifiableIntegersFunc operator-(const ModifiableIntegersFunc& lhs, const ModifiableIntegersFunc& rhs);