#include "Types/Asset.h"

XXH64_hash_t& Asset::getUID() { return UID; }

void Asset::load(std::string path)
{
}

Asset::Asset(XXH64_hash_t uid) : UID(uid) {}
