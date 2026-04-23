#include "Types/CollisionShapes/Circle.h"

Vector2f Circle::get_MinMaxX() { return { Position.x + Radius, Position.y }; }
Vector2f Circle::get_MinMaxY() { return { Position.x, Position.y + Radius }; }
Vector2f Circle::get_Center() { return Position; }

Circle::Circle(Vector2f pos, float radius, Effigy& val) :
	CollidingShape(val),
	Position(pos),
	Radius(radius)
{
	Complexity = CIRCLE;
}

Vector2f& Circle::get_Position() { return Position; }
void Circle::set_Position(Vector2f pos) { Position = pos; }
void Circle::add_Position(Vector2f pos) { Position += pos; }
float& Circle::get_Radius() { return Radius; }

