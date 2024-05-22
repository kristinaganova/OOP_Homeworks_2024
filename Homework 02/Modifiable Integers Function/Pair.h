#pragma once
#pragma once
#include <cstdint>

struct Pair
{
	int16_t a = 0, b = 0;
	Pair(int16_t a, int16_t b) :a(a), b(b) {}
	Pair() = default;
};
