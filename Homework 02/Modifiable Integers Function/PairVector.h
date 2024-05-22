#pragma once
#include "Pair.h"
#include <iostream>
#include <fstream>
#include <cstdint>

class PairVector
{
private:
    Pair* pairs;
    size_t size;
    size_t capacity;

public:
    PairVector(size_t initialCapacity = 4);
    ~PairVector();
    PairVector(const PairVector& other);
    PairVector& operator=(const PairVector& other);
    PairVector(PairVector&& other) noexcept;
    PairVector& operator=(PairVector&& other) noexcept;

    void addPair(const Pair& pair);
    Pair& operator[](size_t index);
    const Pair& operator[](size_t index) const;
    void popAt(unsigned index);
    int16_t contains(int16_t a) const;
    bool unique() const;
    size_t getSize() const;   
    void serialize(const char* filename) const;
    void serialize(std::ofstream& ofs) const;
    void deserialize(const char* filename);
    void deserialize(std::ifstream& ifs);
    friend class ModifiableIntegersFunc;

private:
    void resize(size_t newCapacity);
    void free();
    void copyFrom(const PairVector& other);
    void moveFrom(PairVector&& other);

};