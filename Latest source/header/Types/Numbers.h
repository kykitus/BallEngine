#ifndef BE_NUMBERS
#define BE_NUMBERS

#include <xxHash/xxhash.h>

#include <vector>
#include <string>

#include "Types/Vectors.h"

enum sign
{
	NEGATIVE = -1,
	ZERO,
	POSITIVE
};

// Return either -1, 0 or 1 based on sign of number
template <typename T>
int sgn(T val);

// 
std::vector<int> resolve_TextIntArray(std::string text);

// Returns hash value out of two numbers
int cantor_hash(int x, int y);

XXH64_hash_t getUIDfromString(std::string str);
XXH64_hash_t getUIDfromString(const char* str);
#endif
