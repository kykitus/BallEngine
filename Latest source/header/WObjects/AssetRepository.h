#ifndef BE_ASSETREPOSITORY
#define BE_ASSETREPOSITORY

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <string>
#include <unordered_map>
#include <iostream>

#include "Types/Numbers.h"
#include "Types/Asset.h"

class AssetRepository
{
public:

	template<typename T>
	T* requestbyString(std::string path) 
	{
		T* asset = new T;
		if (asset.load(path)) { std::invalid_argument("Couldn't load asset on: " + path); };
		Repository[getUIDfromString(path)] = asset;
	};

	Asset* requestbyUID(XXH64_hash_t uid);

	void delete_AssetbyString(std::string path);
	void delete_AssetbyUID(XXH64_hash_t uid);
	void flush();

	size_t size();

	AssetRepository() = default;
	~AssetRepository();

private:

	std::unordered_map<XXH64_hash_t, Asset*> Repository;

};

#endif