#include "BallEngine/Elements/Elements.h"

void CollisionPlane::set_Collision(std::string collision_planes)
{
	std::vector<int> new_col = resolve_TextIntArray(collision_planes);
	CollisionLayers = new_col;
	CollisionMasks = new_col;
}
void CollisionPlane::set_Collision(std::vector<int> collision_planes) { CollisionLayers = collision_planes; CollisionMasks = collision_planes; }

void CollisionPlane::set_CollisionLayers(std::vector<int> collision_planes) { CollisionLayers = collision_planes; }
void CollisionPlane::set_CollisionMasks(std::vector<int> collision_planes) { CollisionLayers = collision_planes; }
std::vector<int>& CollisionPlane::get_CollisionLayers() { return CollisionLayers; }
std::vector<int>& CollisionPlane::get_CollisionMasks() { return CollisionMasks; }

CollisionPlane::CollisionPlane(std::pair<std::vector<int>, std::vector<int>> collision_planes) :
	CollisionLayers(collision_planes.first),
	CollisionMasks(collision_planes.second) {}

