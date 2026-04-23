#include "BallEngine/DataStructures/ResourceRepositiory.h"

// TEXTURE REPOSITORY

GPU_Image* Texture_Repository::request(std::string path)
{
	if (Repository.find(path) == Repository.end()) {

		Repository[path] = GPU_LoadImage(path.c_str());
	}

	if (Repository[path] == nullptr) { GPU_LogError("Image Failed To Load"); }

	return Repository[path];
}

void Texture_Repository::delete_Texture(std::string path)
{
	GPU_FreeImage(Repository[path]);
	Repository.erase(path);
}

void Texture_Repository::flush()
{
	for (auto& [key, tex] : Repository)
	{
		GPU_FreeImage(tex);
		tex = nullptr;
	}
	Repository.clear();
}

size_t Texture_Repository::size()
{
	return Repository.size();
}

Texture_Repository::~Texture_Repository() { flush(); }

