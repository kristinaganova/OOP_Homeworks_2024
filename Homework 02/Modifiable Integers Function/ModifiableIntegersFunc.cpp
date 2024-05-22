#include "ModifiableIntegersFunc.h"
#include <fstream>

void ModifiableIntegersFunc::computeInjective()
{
	if ((results.getSize() == results.unique()))
	{
		type.setInjective();
	}
}

void ModifiableIntegersFunc::computeSurjective()
{
	if (results.getSize() == (-INT16_MIN + INT16_MAX + 1))
	{
		type.setSurjective();
	}
}

ModifiableIntegersFunc::ModifiableIntegersFunc(int16_t(*func)(int16_t)) : func(func)
{
	results.resize(INT16_MAX - INT16_MIN + 1);
	computeResults();
	computeInjective();
	computeSurjective();
}

void ModifiableIntegersFunc::computeResults()
{
	for (int16_t i = INT16_MIN; i < INT16_MAX; ++i)
	{
		results.addPair(Pair(i, func(i)));
	}
}

bool ModifiableIntegersFunc::isNotInExcludedPoints(int16_t point) const
{
	for (int i = 0; i < excludedPoints.getSize(); i++)
	{
		if (point == excludedPoints[i])
		{
			return false;
		}
	}
	return true;
}

bool ModifiableIntegersFunc::isInjective() const
{
	return type.isInjective();
}

bool ModifiableIntegersFunc::isSurjective() const
{
	return type.isSurjective();
}

bool ModifiableIntegersFunc::isBijective() const
{
	return type.isInjective() && type.isSurjective();
}

void ModifiableIntegersFunc::inverse()
{
	if (!isInjective())
	{
		throw std::logic_error("Function is not injective. It is not invertible.");
	}

	PairVector inverseResults;
	PairVector customInverseResults;

	for (size_t i = 0; i < customResults.getSize(); i++)
	{
		if (isNotInExcludedPoints(i))
		{
			int16_t y = this->operator()(customResults[i].a);
			customInverseResults.addPair(Pair(y, customResults[i].a));
		}
	}

	for (int16_t x = INT16_MIN; x <= INT16_MAX; ++x)
	{
		if (isNotInExcludedPoints(x))
		{
			int16_t y = this->operator()(x);
			inverseResults.addPair(Pair(y, x));
		}
	}

	results = inverseResults;
	customResults = customInverseResults;
	computeInjective();
	computeSurjective();
}

void ModifiableIntegersFunc::plot(int16_t x1, int16_t x2) const
{
	const int plotSize = 21;
	const int gridSize = plotSize - 1;
	char plot[plotSize][plotSize];

	for (int i = 0; i < plotSize; ++i)
	{
		for (int j = 0; j < plotSize; ++j)
		{
			plot[i][j] = ' ';
		}
	}

	int16_t y1 = INT16_MAX;
	int16_t y2 = INT16_MIN;
	bool rangeComputed = false;
	for (int16_t x = x1; x <= x2; ++x)
	{
		if (this->isNotInExcludedPoints(x))
		{
			int16_t y = this->operator()(x);
			if (!rangeComputed || y < y1)
			{
				y1 = y;
			}
			if (!rangeComputed || y > y2)
			{
				y2 = y;
			}
			rangeComputed = true;
		}
	}

	if (y2 - y1 < 20)
		y2 = y1 + 20;

	for (int16_t x = x1; x <= x2; ++x)
	{
		if (this->isNotInExcludedPoints(x))
		{
			int16_t y = this->operator()(x);
			int gridX = (x - x1) * gridSize / (x2 - x1);
			int gridY;
			if (y2 - y1 != 0)
			{
				gridY = gridSize - 1 - (y - y1) * gridSize / (y2 - y1);
			}
			else
			{
				gridY = gridSize / 2;
			}
			if (gridX >= 0 && gridX < plotSize && gridY >= 0 && gridY < plotSize)
			{
				plot[gridY][gridX] = '*';
			}

		}
	}

	for (int i = 0; i < plotSize; ++i)
	{
		for (int j = 0; j < plotSize; ++j)
		{
			std::cout << plot[i][j];
		}
		std::cout << std::endl;
	}
}

void ModifiableIntegersFunc::setCustomResults(int16_t input, int16_t result)
{
	if (excludedPoints.contains(input))
	{
		throw std::logic_error("Input is in the excluded points!");
	}

	customResults.addPair(Pair(input, result));
	computeInjective();
	computeSurjective();
}

void ModifiableIntegersFunc::excludePoint(int16_t input)
{
	if (!excludedPoints.contains(input))
	{
		excludedPoints.pushBack(input);
	}
}

int16_t ModifiableIntegersFunc::operator()(int16_t input) const
{
	for (size_t i = 0; i < customResults.getSize(); i++)
	{
		if (customResults[i].a == input)
		{
			return customResults[i].b;
		}
	}
	if (excludedPoints.contains(input))
	{
		throw std::exception("The function is not defined for this input");
	}
	return func(input); //easier to calculate than to search in the results
}

int16_t ModifiableIntegersFunc::operator()(const ModifiableIntegersFunc& other, int16_t input) const
{
	for (size_t i = 0; i < results.getSize(); i++)
	{
		if (results[i].a == input)
		{
			return customResults[i].b;
		}
	}
	if (excludedPoints.contains(input))
	{
		throw std::exception("The function is not defined for this input");
	}
	return this->func(other.func(input));
}

ModifiableIntegersFunc operator-(const ModifiableIntegersFunc& lhs, const ModifiableIntegersFunc& rhs)
{
	ModifiableIntegersFunc result = lhs;
	result -= rhs;
	return result;
}

ModifiableIntegersFunc operator+(const ModifiableIntegersFunc& lhs, const ModifiableIntegersFunc& rhs)
{
	ModifiableIntegersFunc result = lhs;
	result += rhs;
	return result;
}

void ModifiableIntegersFunc::operator+=(const ModifiableIntegersFunc& other)
{
	for (size_t i = 0; i < other.customResults.getSize(); ++i)
	{
		customResults.addPair(other.customResults[i]);
	}

	for (size_t i = 0; i < other.excludedPoints.getSize(); ++i)
	{
		excludedPoints.pushBack(other.excludedPoints[i]);
	}

	for (int i = 0; i < results.getSize(); i++)
	{
		results[i].b += other.results[i].b;
	}

	computeInjective();
	computeSurjective();
}

void ModifiableIntegersFunc::operator-=(const ModifiableIntegersFunc& other)
{
	for (size_t i = 0; i < other.customResults.getSize(); ++i)
	{
		for (size_t j = 0; j < customResults.getSize(); ++j)
		{
			if (customResults[j].a == other.customResults[i].a)
			{
				customResults.popAt(j);
				break;
			}
		}
	}

	for (size_t i = 0; i < other.excludedPoints.getSize(); ++i)
	{
		for (size_t j = 0; j < excludedPoints.getSize(); ++j)
		{
			if (excludedPoints[j] == other.excludedPoints[i])
			{
				excludedPoints.popAt(j);
				break;
			}
		}
	}

	for (int i = 0; i < results.getSize(); i++)
	{
		results[i].b -= other.results[i].b;
	}

	computeInjective();
	computeSurjective();
}

int16_t ModifiableIntegersFunc::operator^(const Pair& pairOfKAndX) const
{
	if (pairOfKAndX.a < 1)
	{
		throw std::invalid_argument("Exponent must be at least 1");
	}

	int result = pairOfKAndX.b;
	for (size_t i = 0; i < pairOfKAndX.a; i++)
	{
		result = func(result);
	}
	return result;
}

void ModifiableIntegersFunc::serialize(const char* filename) const
{
	std::ofstream ofs(filename, std::ios::binary);
	if (!ofs.is_open())
	{
		throw std::logic_error("File not found!");
	}
	serialize(ofs);
	ofs.close();
}

void ModifiableIntegersFunc::serialize(std::ofstream& ofs) const
{
	ofs.write((const char*)&type, sizeof(type));
	excludedPoints.serialize(ofs);
	customResults.serialize(ofs);
	results.serialize(ofs);
}

void ModifiableIntegersFunc::deserialize(const char* filename)
{
	std::ifstream ifs(filename, std::ios::binary);
	if (!ifs.is_open())
	{
		throw std::logic_error("Failed to open file for writing!");
	}

	deserialize(ifs);

	ifs.close();
}

void ModifiableIntegersFunc::deserialize(std::ifstream& ifs)
{
	ifs.read((char*)&type, sizeof(type));
	excludedPoints.deserialize(ifs);
	customResults.deserialize(ifs);
	results.deserialize(ifs);
}

bool operator||(const ModifiableIntegersFunc& f1, const ModifiableIntegersFunc& f2)
{
	constexpr double epsilon = 1e-6;
	bool definedAtLeastTwoPoints = false;
	int16_t x1 = INT16_MIN, x2 = INT16_MIN;

	for (int16_t x = INT16_MIN; x < INT16_MAX; ++x)
	{
		if (f1.isNotInExcludedPoints(x) && f2.isNotInExcludedPoints(x))
		{
			if (!definedAtLeastTwoPoints)
			{
				x1 = x;
				definedAtLeastTwoPoints = true;
			}
			else if (x != x1)
			{
				x2 = x;
				break;
			}
		}
	}

	if (definedAtLeastTwoPoints)
	{
		double slope1 = (double)(f1(x2) - f1(x1)) / (x2 - x1);
		double slope2 = (double)(f2(x2) - f2(x1)) / (x2 - x1);
		return std::abs(slope1 - slope2) < epsilon;
	}

	return true;
}

bool operator<(const ModifiableIntegersFunc& lhs, const ModifiableIntegersFunc& rhs)
{
	for (int16_t x = INT16_MIN; x < INT16_MAX; ++x)
	{
		int16_t lhsOutput = lhs.isNotInExcludedPoints(x) ? lhs.func(x) : INT16_MIN;
		int16_t rhsOutput = rhs.isNotInExcludedPoints(x) ? rhs.func(x) : INT16_MIN;
		if (lhsOutput >= rhsOutput)
		{
			return false;
		}
	}
	return true;
}

bool operator<=(const ModifiableIntegersFunc& lhs, const ModifiableIntegersFunc& rhs)
{
	return !(rhs < lhs);
}

bool operator==(const ModifiableIntegersFunc& lhs, const ModifiableIntegersFunc& rhs)
{
	return !(lhs < rhs) && !(rhs < lhs);
}

bool operator!=(const ModifiableIntegersFunc& lhs, const ModifiableIntegersFunc& rhs)
{
	return !(lhs == rhs);
}

bool operator>=(const ModifiableIntegersFunc& lhs, const ModifiableIntegersFunc& rhs)
{
	return !(lhs < rhs);
}

bool operator>(const ModifiableIntegersFunc& lhs, const ModifiableIntegersFunc& rhs)
{
	return rhs < lhs;
}