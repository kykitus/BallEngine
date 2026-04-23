#ifndef BE_ASSET
#define BE_ASSET

#include <xxHash/xxhash.h>

#include <string>


class Asset 
{
public:

	virtual void load(std::string path);

	Asset() = default;
	Asset(XXH64_hash_t uid);

	XXH64_hash_t& getUID();

private:

	XXH64_hash_t UID;

};

#endif