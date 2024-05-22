#include "PairVector.h"

PairVector::PairVector(size_t initialCapacity) :size(0), capacity(initialCapacity)
{
	pairs = new Pair[initialCapacity];
}

PairVector::~PairVector()
{
	free();
}

PairVector::PairVector(const PairVector& other)
{
	copyFrom(other);
}

PairVector& PairVector::operator=(const PairVector& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

PairVector::PairVector(PairVector&& other) noexcept
{
	moveFrom(std::move(other));
}

PairVector& PairVector::operator=(PairVector&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

void PairVector::addPair(const Pair& pair)
{
	if (size == capacity)
	{
		resize(capacity * 2);
	}
	pairs[size++] = pair;
}

Pair& PairVector::operator[](size_t index)
{
	if (index >= size)
	{
		throw std::out_of_range("Index out of range!");
	}

	return pairs[index];
}

const Pair& PairVector::operator[](size_t index) const
{
	if (index >= size)
	{
		throw std::out_of_range("Index out of range!");
	}

	return pairs[index];
}

void PairVector::popAt(unsigned index)
{
	if (index > size)
	{
		throw std::out_of_range("Index out of range");
	}
	Pair temp = pairs[index];
	size--;
	for (size_t i = index; i < size; i++)
	{
		pairs[i] = pairs[i + 1];
	}
}

int16_t PairVector::contains(int16_t a) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (pairs[i].a == a)
		{
			return i;
		}
	}
	return 0;
}

bool PairVector::unique() const
{
	for (size_t i = 0; i < size - 1; ++i)
	{
		for (size_t j = i + 1; j < size; ++j)
		{
			if (pairs[i].b == pairs[j].b)
			{
				return false;
			}
		}
	}
	return true;
}

size_t PairVector::getSize() const
{
	return size;
}

void PairVector::resize(size_t newCapacity)
{
	Pair* newArray = new Pair[newCapacity];
	for (size_t i = 0; i < size; ++i)
	{
		newArray[i] = std::move(pairs[i]);
	}
	delete[] pairs;
	pairs = newArray;
	capacity = newCapacity;
}

void PairVector::free()
{
	delete[] pairs;
	pairs = nullptr;
	size = 0;
	capacity = 0;
}

void PairVector::copyFrom(const PairVector& other)
{
	this->size = other.size;
	this->pairs = new Pair[other.size];
	for (int i = 0; i < size; i++)
	{
		this->pairs[i] = other.pairs[i];
	}
	this->capacity = other.capacity;
}

void PairVector::moveFrom(PairVector&& other)
{
	this->pairs = other.pairs;
	this->capacity = other.capacity;
	this->size = other.size;
	other.pairs = nullptr;
	other.capacity = other.size = 0;
}

void PairVector::serialize(const char* filename) const
{
	std::ofstream ofs(filename, std::ios::binary);
	if (!ofs.is_open())
	{
		throw std::logic_error("Failed to open file for writing!");
	}

	serialize(ofs);

	ofs.close();
}

void PairVector::serialize(std::ofstream& ofs) const
{
	ofs.write((const char*)&size, sizeof(size));
	ofs.write((const char*)pairs, size * sizeof(Pair));
}

void PairVector::deserialize(const char* filename) 
{
	std::ifstream ifs(filename, std::ios::binary);
	if (!ifs.is_open())
	{
		throw std::logic_error("Failed to open file for writing!");
	}

	deserialize(ifs);

	ifs.close();
}

void PairVector::deserialize(std::ifstream& ifs) 
{
	ifs.read((char*)&size, sizeof(size));
	ifs.read((char*)pairs, size * sizeof(Pair));
}