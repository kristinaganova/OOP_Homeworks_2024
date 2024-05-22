#include "MultiSet.h"
#include <fstream>

namespace
{
	unsigned int myAbs(int a)
	{
		return a < 0 ? -a : a;
	}
	unsigned int myMin(unsigned int a, unsigned int b)
	{
		return a < b ? a : b;
	}
	unsigned int myMax(unsigned int a, unsigned int b)
	{
		return a > b ? a : b;
	}
}

void MultiSet::moveFrom(MultiSet&& other) noexcept
{
	this->n = other.n;
	this->k = other.k;
	this->data = other.data;
	other.data = nullptr;
	other.n = other.k = 0;
}

void MultiSet::copyFrom(const MultiSet& other)
{
	unsigned int bucketsCount = other.getBucketCount();
	this->data = new unsigned char[bucketsCount];
	for (size_t i = 0; i < bucketsCount; i++)
	{
		this->data[i] = other.data[i];
	}
	this->n = other.n;
	this->k = other.k;
}

void MultiSet::free()
{
	delete[] data;
	data = nullptr;
	n = k = 0;
}

unsigned char MultiSet::getKBitsFromIndex(unsigned int index, unsigned int bitOffset) const
{
	unsigned int bucketsCount = getBucketCount();
	if (index > bucketsCount * MAX_BITS_IN_CHAR)
	{
		throw std::out_of_range("Invalid index");
	}

	unsigned char mask = (1 << k) - 1;
	unsigned char value = (data[index] >> bitOffset) & mask;

	if (bitOffset + k > MAX_BITS_IN_CHAR && index + 1 < bucketsCount)
	{
		value |= (data[index + 1] << (MAX_BITS_IN_CHAR - bitOffset)) & mask;
	}
	return value;
}

void MultiSet::setKBitsAtIndex(unsigned int index, unsigned int bitOffset, unsigned char newValue)
{
	unsigned int bucketsCount = getBucketCount();
	if (index > bucketsCount * MAX_BITS_IN_CHAR)
	{
		throw std::out_of_range("Invalid index");
	}

	unsigned char mask = (1 << k) - 1;
	data[index] &= ~(mask << bitOffset);
	data[index] |= (newValue << bitOffset) & (mask << bitOffset);

	if (bitOffset + k > MAX_BITS_IN_CHAR && index + 1 < getBucketCount())
	{
		data[index + 1] &= ~(mask >> (MAX_BITS_IN_CHAR - bitOffset));
		data[index + 1] |= (newValue >> (MAX_BITS_IN_CHAR - bitOffset));
	}
}

MultiSet::MultiSet(unsigned int n, unsigned int k) : n(n)
{
	setK(k);
	this->data = new unsigned char[getBucketCount()] {0};
}

MultiSet& MultiSet::operator=(const MultiSet& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

MultiSet& MultiSet::operator=(MultiSet&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

MultiSet::MultiSet(const MultiSet& other)
{
	copyFrom(other);
}

MultiSet::MultiSet(MultiSet&& other) noexcept
{
	moveFrom(std::move(other));
}

MultiSet::~MultiSet()
{
	free();
}

void MultiSet::setK(unsigned int k)
{
	if (k > MAX_BITS_IN_CHAR || k == 0)
	{
		throw std::out_of_range("K should be between 1 and 8");
	}
	this->k = k;
}

void MultiSet::add(unsigned int number)
{
	unsigned int index = getIndexOfNumber(number);
	unsigned int offset = getOffsetOfNumber(number);
	unsigned char value = getKBitsFromIndex(index, offset);

	if (value < (1 << k) - 1)
	{
		value++;
		setKBitsAtIndex(index, offset, value);
	}
}

void MultiSet::print() const
{
	for (unsigned int i = 0; i <= n; ++i)
	{
		unsigned int index = getIndexOfNumber(i);
		unsigned int offset = getOffsetOfNumber(i);
		unsigned char value = getKBitsFromIndex(index, offset);

		for (int j = 0; j < value; ++j)
		{
			std::cout << i << " ";
		}
	}
	std::cout << std::endl;
}

unsigned int MultiSet::getCount(unsigned int number) const
{
	unsigned int index = getIndexOfNumber(number);
	unsigned int offset = getOffsetOfNumber(number);
	unsigned char value = getKBitsFromIndex(index, offset);
	return value % ((1 << k) - 1);
}

unsigned int MultiSet::getBucketCount() const
{
	unsigned int allBits = (n + 1) * k;
	unsigned int result = allBits / 8;
	return (allBits % 8 != 0) ? result + 1 : result; //for odd k we need one more bucket
}

unsigned int MultiSet::getIndexOfNumber(unsigned int number) const
{
	return (number * k) / MAX_BITS_IN_CHAR;
}

unsigned int MultiSet::getOffsetOfNumber(unsigned int number) const
{
	return (number * k) % MAX_BITS_IN_CHAR;
}

void MultiSet::printMemoryRepresentation() const
{
	unsigned int bucketsCount = getBucketCount();

	for (int i = 0; i < bucketsCount; ++i)
	{
		for (int j = MAX_BITS_IN_CHAR - 1; j >= 0; --j)
		{
			std::cout << ((data[i] >> j) & 1);
		}
		std::cout << " ";
	}
	std::cout << std::endl;
}

std::ofstream& operator<<(std::ofstream& os, const MultiSet& ms)
{
	os.write((const char*)(&ms.n), sizeof(unsigned int));
	os.write((const char*)(&ms.k), sizeof(unsigned int));
	unsigned int bucketsCount = ms.getBucketCount();
	os.write((const char*)(ms.data), bucketsCount);
	return os;
}

std::ifstream& operator>>(std::ifstream& is, MultiSet& ms)
{
	is.read((char*)(&ms.n), sizeof(unsigned int));
	is.read((char*)(&ms.k), sizeof(unsigned int));
	unsigned int bucketsCount = ms.getBucketCount();
	ms.data = new unsigned char[bucketsCount] { 0 };
	is.read((char*)(ms.data), bucketsCount);
	return is;
}

MultiSet operator-(const MultiSet& set)
{
	unsigned int bucketsCount = (set.n * set.k) / MAX_BITS_IN_CHAR + 1;
	MultiSet result(set.n, set.k);

	for (int i = 0; i < bucketsCount; ++i)
	{
		result.data[i] = ~set.data[i];
	}
	return result;
}

MultiSet getResultFromSetOperation(const MultiSet& lhs, const MultiSet& rhs, unsigned int(*func)(unsigned int, unsigned int), unsigned int(*funcForN)(unsigned int, unsigned int))
{
	if (lhs.k != rhs.k)
	{
		throw std::invalid_argument("Multisets have different k values.");
	}

	unsigned int resultN = funcForN(lhs.n, rhs.n);
	MultiSet result(resultN, lhs.k);

	for (int i = 0; i <= resultN; ++i)
	{    
		unsigned int lhsElementsCountAtIndex = lhs.getCount(i);
		unsigned int rhsElementsCountAtIndex = rhs.getCount(i);
		unsigned int resultElementsCountAtIndex = func(lhsElementsCountAtIndex, rhsElementsCountAtIndex);

		for (unsigned int j = 0; j < resultElementsCountAtIndex; ++j)
		{
			result.add(i);
		}
	}
	return result;
}

MultiSet operator|(const MultiSet& lhs, const MultiSet& rhs)
{
	return getResultFromSetOperation(lhs, rhs, [](unsigned int a, unsigned int b) { return a + b; }, [](unsigned int a, unsigned int b) { return myMax(a, b); });
}

MultiSet operator&(const MultiSet& lhs, const MultiSet& rhs)
{
	return getResultFromSetOperation(lhs, rhs, [](unsigned int a, unsigned int b) { return myMin(a, b); }, [](unsigned int a, unsigned int b) { return myMin(a, b); });
}

MultiSet operator/(const MultiSet& lhs, const MultiSet& rhs)
{
	return getResultFromSetOperation(lhs, rhs, [](unsigned int a, unsigned int b) { return (a != 0 ? myAbs(a - b) : 0); }, [](unsigned int a, unsigned int b) { return a; });
}