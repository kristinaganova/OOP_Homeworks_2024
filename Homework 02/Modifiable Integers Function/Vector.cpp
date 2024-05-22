#include "Vector.h"
#include <exception>
#include <cmath>
#include <fstream>

namespace
{
	const short INITIAL_CAPACITY = 4;
	const short RESIZE_COEF = 2;
}

Vector::Vector() : Vector(INITIAL_CAPACITY) { }

Vector::Vector(size_t capacity) : capacity(capacity)
{
	data = new int16_t[capacity];
}

Vector::Vector(Vector&& other) noexcept
{
	moveFrom(std::move(other));
}

Vector& Vector::operator=(Vector&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

Vector::Vector(const Vector& other)
{
	copyFrom(other);
}

Vector& Vector::operator=(const Vector& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Vector::~Vector()
{
	free();
}

void Vector::assertIndex(size_t index) const
{
	if (index >= size) 
	{
		throw std::exception("Out of range");
	}
}

void Vector::upsizeIfNeeded()
{
	if (size == capacity)
	{
		resize(capacity * RESIZE_COEF);
	}
}

void Vector::downsizeIfNeeded()
{
	if (size * RESIZE_COEF * RESIZE_COEF <= capacity)
	{
		resize(capacity / RESIZE_COEF);
	}
}

void Vector::resize(size_t newCapacity)
{
	capacity = newCapacity;
	int16_t* temp = new int16_t[capacity];

	if (size > newCapacity)
	{
		size = newCapacity;
	}

	for (size_t i = 0; i < size; i++)
	{
		temp[i] = data[i];
	}

	delete[] data;
	data = temp;
}

size_t Vector::getSize() const
{
	return size;
}

size_t Vector::getCapacity() const
{
	return capacity;
}

bool Vector::contains(int16_t num) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (data[i] == num)
			return true;
	}
	return false;
}

void Vector::pushBack(int16_t element)
{
	upsizeIfNeeded();
	data[size++] = std::move(element);
}

void Vector::pushAt(int16_t element, size_t index)
{
	assertIndex(index);
	upsizeIfNeeded();

	for (size_t i = size; i > index; i--)
	{
		data[i] = std::move(data[i - 1]);
	}

	data[index] = element;
	size++;
}

int16_t Vector::popBack()
{
	if (empty())
	{
		throw std::exception("Vector is empty");
	}
	downsizeIfNeeded();
	return data[--size];
}

int16_t Vector::popAt(size_t index)
{
	assertIndex(index);
	downsizeIfNeeded();

	int16_t temp = data[index];
	size--;
	for (size_t i = index; i < size; i++)
	{
		data[i] = data[i + 1];
	}

	return temp;
}

bool Vector::empty() const
{
	return size == 0;
}

void Vector::clear()
{
	size = 0;
}

void Vector::shrinkToFit()
{
	resize(size);
}

void Vector::sort()
{
	for (size_t i = 0; i < size - 1; ++i)
	{
		size_t minIndex = i;
		for (size_t j = i + 1; j < size; ++j)
		{
			if (data[j] < data[minIndex])
			{
				minIndex = j;
			}
		}
		int16_t temp = data[i];
		data[i] = data[minIndex];
		data[minIndex] = temp;
	}
}

bool Vector::unique() const
{
	for (size_t i = 0; i < size - 1; ++i)
	{
		for (size_t j = i + 1; j < size; ++j)
		{
			if (data[i] == data[j])
				return false;
		}
	}
	return true;
}

int16_t& Vector::operator[](size_t index)
{
	assertIndex(index);
	return data[index];
}

int16_t Vector::operator[](size_t index) const
{
	assertIndex(index);
	return data[index];
}

void Vector::moveFrom(Vector&& other) noexcept 
{
	data = other.data;
	other.data = nullptr;
	capacity = other.capacity;
	size = other.size;
	other.capacity = other.size = 0;
}

void Vector::copyFrom(const Vector& other)
{
	size = other.size;
	capacity = other.capacity;
	data = new int16_t[capacity];

	for (size_t i = 0; i < other.size; i++)
	{
		data[i] = other.data[i];
	}
}

void Vector::free()
{
	delete[] data;
	data = nullptr;
	size = capacity = 0;
}

void Vector::serialize(const char* filename) const
{
	std::ofstream ofs(filename, std::ios::binary);
	if (!ofs.is_open())
	{
		throw std::logic_error("Failed to open file for writing!");
	}

	serialize(ofs);

	ofs.close();
}

void Vector::serialize(std::ofstream& ofs) const
{
	ofs.write((const char*)&size, sizeof(size));
	ofs.write((const char*)data, size);
}

void Vector::deserialize(const char* filename)
{
	std::ifstream ifs(filename, std::ios::binary);
	if (!ifs.is_open())
	{
		throw std::logic_error("Failed to open file for writing!");
	}

	deserialize(ifs);

	ifs.close();
}

void Vector::deserialize(std::ifstream& ifs)
{
	ifs.read((char*)&size, sizeof(size));
	ifs.read((char*)data, size);
}
