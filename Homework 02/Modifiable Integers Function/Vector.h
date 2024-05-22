#pragma once
#include <cstdint>
#include<iostream>
#include <fstream>

class Vector
{
private:
	int16_t* data = nullptr;
	size_t size = 0;
	size_t capacity;

	void resize(size_t newCapacity);

	void assertIndex(size_t index) const;
	void upsizeIfNeeded();
	void downsizeIfNeeded();
public:
	Vector();
	Vector(size_t capacity);
	Vector(Vector&& other) noexcept;
	Vector& operator=(Vector&& other) noexcept;
	Vector(const Vector& other);
	Vector& operator=(const Vector& other);
	~Vector();

	size_t getSize() const;
	size_t getCapacity() const;

	bool contains(int16_t num) const;

	void pushBack(int16_t element);
	void pushAt(int16_t element, size_t index);
	int16_t popBack();
	int16_t popAt(size_t index);

	bool empty() const;
	void clear();
	void shrinkToFit();
	void sort();
	bool unique() const;

	int16_t& operator[](size_t index);
	int16_t operator[](size_t index) const;

	void serialize(const char* filename) const;
	void serialize(std::ofstream& ofs) const;
	void deserialize(const char* filename);
	void deserialize(std::ifstream& ifs);

	friend class ModifiableIntegersFunc;
private:
	void moveFrom(Vector&& other) noexcept;
	void copyFrom(const Vector& other);
	void free();
};

