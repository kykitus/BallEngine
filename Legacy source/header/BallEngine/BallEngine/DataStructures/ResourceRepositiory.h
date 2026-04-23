#ifndef SDL_ENGINE_RESOURCE_REPOSITORY
#define SDL_ENGINE_RESOURCE_REPOSITORY

#include "BallEngine/Types.h"

// TEXTURE REPOSITORY

class Texture_Repository
{
public:

	GPU_Image* request(std::string path);
	void delete_Texture(std::string path);
	void flush();

	size_t size();

	Texture_Repository() = default;

	~Texture_Repository();
private:

	std::unordered_map<std::string, GPU_Image*> Repository;

};

//

#endif