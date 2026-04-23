#include "Types/CollisionShapes/Point.h"
#include "SphereCore.h"

Vector2f Dot::get_MinMaxX() { return {Position.x, Position.x}; }
Vector2f Dot::get_MinMaxY() { return {Position.y, Position.y}; }
Vector2f Dot::get_Center() { return Position; }

Vector2f& Dot::get_Position() { return Position; }
void Dot::set_Position(Vector2f val) 
{
	Root->get_CollisionMap()->flush(this, HashBelonging.second);
	Position = val;
	HashBelonging = Root->get_CollisionMap()->where(this, { 1 }, { 1 });
	check_Collision();
}
void Dot::add_Position(Vector2f val) { Position += val; }

Dot::Dot(Vector2f pos, Effigy& val) : 
	CollidingShape(val),
	Position(pos)
{
	HashBelonging = Root->get_CollisionMap()->where(this, {1}, {1});
	Complexity = DOT;
}
