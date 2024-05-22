#pragma once
#include <iostream>

namespace
{
    constexpr int  MAX_BITS_IN_CHAR = 8;
    constexpr int MIN_K = 1;
}

class MultiSet
{
private:
    void moveFrom(MultiSet&& other) noexcept;
    void copyFrom(const MultiSet& other);
    void free();

    void setK(unsigned int k);
    unsigned char getKBitsFromIndex(unsigned int index, unsigned int bitOffset) const;
    void setKBitsAtIndex(unsigned int index, unsigned int bitOffset, unsigned char newValue);
    unsigned int getBucketCount() const;
    unsigned int getIndexOfNumber(unsigned int number) const;
    unsigned int getOffsetOfNumber(unsigned int number) const;
public:
    MultiSet() = default;
    MultiSet(unsigned int n, unsigned int k);
    MultiSet& operator=(const MultiSet& other);
    MultiSet& operator=(MultiSet&& other) noexcept;
    MultiSet(const MultiSet& other);
    MultiSet(MultiSet&& other) noexcept;
    ~MultiSet();

    void add(unsigned int number);
    unsigned int getCount(unsigned int number) const;
    void print() const;
    void printMemoryRepresentation() const;
    void serialize(const char* filename) const;
    void deserialize(const char* filename);

    friend MultiSet getResultFromSetOperation(const MultiSet& lhs, const MultiSet& rhs, unsigned int(*func)(unsigned int, unsigned int), unsigned int(*funcForN)(unsigned int, unsigned int));
    friend std::ofstream& operator<<(std::ofstream& os, const MultiSet& ms);
    friend std::ifstream& operator>>(std::ifstream& os, MultiSet& ms);
    friend MultiSet operator-(const MultiSet& set); //complement ~A
    friend MultiSet operator|(const MultiSet& lhs, const MultiSet& rhs); // union
    friend MultiSet operator&(const MultiSet& lhs, const MultiSet& rhs); // intersection
    friend MultiSet operator/(const MultiSet& lhs, const MultiSet& rhs); // difference A/B
private:
    unsigned int n = MAX_BITS_IN_CHAR;
    unsigned int k = MIN_K;
    unsigned char* data = nullptr;
};