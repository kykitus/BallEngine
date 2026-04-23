#include "WObjects/AssetRepository.h"



Asset* AssetRepository::requestbyUID(XXH64_hash_t uid)
{
	if (!Repository.count(uid)) { std::invalid_argument("There is no asset with this UID"); }
	else { return Repository[uid]; }
}

void AssetRepository::delete_AssetbyString(std::string path)
{
	Repository.erase(getUIDfromString(path));
}

void AssetRepository::delete_AssetbyUID(XXH64_hash_t uid)
{
	Repository.erase(uid);
}

void AssetRepository::flush()
{
	for (auto& [key, asset] : Repository)
	{
		delete asset;
	}
	Repository.clear();
}

size_t AssetRepository::size()
{
	return Repository.size();
}

AssetRepository::~AssetRepository() { flush(); }

