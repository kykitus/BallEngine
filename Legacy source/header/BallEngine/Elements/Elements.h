#ifndef SDL_ENGINE_ELEMENTS
#define SDL_ENGINE_ELEMENTS

#include "BallEngine/Types.h"

class CollisionPlane 
{
public:

	void set_Collision(std::string collision_planes);
	void set_Collision(std::vector<int> collision_planes);
	void set_CollisionLayers(std::vector<int> collision_planes);
	void set_CollisionMasks(std::vector<int> collision_planes);
	std::vector<int>& get_CollisionLayers();
	std::vector<int>& get_CollisionMasks();

	CollisionPlane(std::pair<std::vector<int>, std::vector<int>> collision_planes);

private:

	std::vector<int> CollisionLayers; // places, where your object is seen
	std::vector<int> CollisionMasks; // places, you see objects

};

#endif
