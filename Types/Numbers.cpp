#include "Types/Numbers.h"

// SGN

template <typename T>
int sgn(T val)
{
	return (T(0) < val) - (val < T(0));
}

template int sgn<int>(int val);
template int sgn<float>(float val);

//



// TEXT TO INT

std::vector<int> resolve_TextIntArray(std::string text)
{
	std::vector<int> list;
	short int last = 0;
	int num = 0;
	for (int type = 0; type <= text.length(); type++)
	{
		if (text[type] == 44)
		{
			num = std::stoi(text.substr(last, type - last));
			last = type + 1;
			list.push_back(num);
		}
	}
	return list;
}

//



// CANTOOR HASH

int cantor_hash(int x, int y) { return 0.5 * (x + y) * (x + y + 1) + y; }

//



// GET UID FROM STRING

XXH64_hash_t getUIDfromString(std::string str) { return XXH64(str.data(), sizeof(str), 0); }
XXH64_hash_t getUIDfromString(const char* str) { return XXH64(str, sizeof(str), 0); }

//


