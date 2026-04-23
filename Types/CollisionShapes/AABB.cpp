#include "Types/CollisionShapes/AABB.h"

#include "SphereCore.h"

SDL_FRect& AABB::get_Rect() { return Rect; }

Vector2f AABB::get_Position() { return Vector2f{ Rect.x, Rect.y }; }
void AABB::set_Position(Vector2f val) 
{
	Root->get_CollisionMap()->flush(this, HashBelonging.second);
	Rect.x = val.x; Rect.y = val.y;
	HashBelonging = Root->get_CollisionMap()->where(this, { 1 }, { 1 });
	check_Collision();

}
void AABB::add_Position(Vector2f val) { Rect.x += val.x; Rect.y += val.y; }
void AABB::set_Size(Vector2f val) { Rect.w = val.x; Rect.h = val.y; }

Vector2f AABB::get_MinMaxX() { return Vector2f{ Rect.x, Rect.x + Rect.w }; }
Vector2f AABB::get_MinMaxY() { return  Vector2f{ Rect.y, Rect.y + Rect.h }; }

Vector2f AABB::get_Center() { return { Rect.x + 0.5f * Rect.w, Rect.y + 0.5f * Rect.h }; }
void AABB::set_Center(Vector2f val) { Rect.x = val.x - 0.5f * Rect.w; Rect.y = val.y - 0.5f * Rect.h; }
Vector2f AABB::get_HalfSize() { return { Rect.w * 0.5f, Rect.h * 0.5f }; }

AABB::AABB(Vector2f pos, Vector2f size, Effigy& val) : CollidingShape(val)
{
	Rect.x = pos.x;
	Rect.y = pos.y;
	Rect.w = size.x;
	Rect.h = size.y;
	HashBelonging = Root->get_CollisionMap()->where(this, { 1 }, { 1 });
	Complexity = BOX;
}