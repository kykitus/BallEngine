#include "BallEngine/Elements/CollisionPhysics.h"
#include "BallEngine/Global.h"
#include "BallEngine/EngineCore.h"

Hit::Hit() :
	Collider(0),
	Position(0,0),
	Depth(0,0),
	Normal(0,0),
	time(0)
{}
Hit::Hit(Colliding_Shape* col, Vector2f pos, Vector2f overlap, Vector2f direction, float length) 	:
	Collider(col),
	Position(pos),
	Depth(overlap),
	Normal(direction),
	time(length)
{}

Sweep::Sweep(Hit hit, Vector2f pos, float length) :
	Point(hit),
	Position(pos),
	time(length)
{}



// SHAPES



Vector2f Colliding_Shape::get_MinMaxX() { return { 0.0f, 0.0f }; }
Vector2f Colliding_Shape::get_MinMaxY() { return { 0.0f, 0.0f }; }

Vector2f Colliding_Shape::get_Center() { return { 0.0f, 0.0f }; }
const int Colliding_Shape::get_Complexity() { return complexity; }

Node& Colliding_Shape::get_Owner() { return *Owner; }
void Colliding_Shape::set_Owner(Node& val) { Owner = &val; }
void Colliding_Shape::set_HashBelonging(std::pair<std::vector<int>, std::vector<int>> val) { HashBelonging = val; }
std::pair<std::vector<int>, std::vector<int>> Colliding_Shape::get_HashBelonging() { return HashBelonging; }

Colliding_Shape::Colliding_Shape(Node& val) : Owner(&val) {}



GPU_Rect& AABB::get_Rect() { return Rect; }

Vector2f AABB::get_Position() { return Vector2f{ Rect.x, Rect.y }; }
void AABB::set_Position(Vector2f val) { Rect.x = val.x; Rect.y = val.y; }
void AABB::add_Position(Vector2f val) { Rect.x += val.x; Rect.y += val.y; }
void AABB::set_Size(Vector2f val) { Rect.w = val.x; Rect.h = val.y; }

Vector2f AABB::get_MinMaxX() {  return Vector2f{ Rect.x, Rect.x + Rect.w }; }
Vector2f AABB::get_MinMaxY() { return  Vector2f{ Rect.y, Rect.y + Rect.h }; }

Vector2f AABB::get_Center() { return { Rect.x + 0.5f * Rect.w, Rect.y + 0.5f * Rect.h }; }
void AABB::set_Center(Vector2f val) { Rect.x = val.x - 0.5f * Rect.w; Rect.y = val.y - 0.5f * Rect.h; }
Vector2f AABB::get_HalfSize() { return { Rect.w * 0.5f, Rect.h * 0.5f }; }

AABB::AABB(Vector2f pos, Vector2f size, Node& val) : Colliding_Shape(val)
{
	Rect.x = pos.x;
	Rect.y = pos.y;
	Rect.w = size.x;
	Rect.h = size.y;
	complexity = BOX;
}


//



Hit AABBPoint(Colliding_Shape* colA, Colliding_Shape* colB) { return Hit(); }

Hit AABBRay(Colliding_Shape* colA, Colliding_Shape* colB) { return Hit(); }
Hit AABBAABB(Colliding_Shape* colA, Colliding_Shape* colB)
{
	AABB* A = dynamic_cast<AABB*>(colA);
	AABB* B = dynamic_cast<AABB*>(colB);

	Vector2f distance =
	{
		B->get_Center().x - A->get_Center().x,
		B->get_Center().y - A->get_Center().y
	};
	Vector2f penetration =
	{ 
		(B->get_HalfSize().x + A->get_HalfSize().x) - abs(distance.x),
		(B->get_HalfSize().y + A->get_HalfSize().y) - abs(distance.y)
	};
	if (penetration.x <= 0 || penetration.y <= 0) { return Hit(); }

	//SDL_SetRenderDrawColor(&Root.get_Renderer(), 100, 255, 100, 255);
	//SDL_RenderDrawRectF(&Root.get_Renderer(), &B->get_Rect());

	if (penetration.x < penetration.y)
	{
		int sign = sgn(distance.x);
		return Hit
		(
			A,
			{ A->get_Center().x + (A->get_HalfSize().x * sign), B->get_Center().y },
			{ (penetration.x + MacroPanel.get_MinShapeDistance()) * sign, 0.0f },
			{ (float)sign, 0.0f },
			0.0f
		);
	}
	else
	{
		int sign = sgn(distance.y);
		return Hit
		(
			A,
			{ B->get_Center().x, A->get_Center().y + (A->get_HalfSize().y * sign) },
			{ 0.0f, (penetration.y + MacroPanel.get_MinShapeDistance()) * sign },
			{ 0.0f, (float)sign },
			0.0f
		);
	}
}

Hit AABBCircle(Colliding_Shape* colA, Colliding_Shape* colB) { return Hit(); }


Hit CircleCircle(Colliding_Shape* colA, Colliding_Shape* colB) { return Hit(); }



IntersectFunction Intersection[4][4] =
{ //Point		Ray			Box			Circle
	{0			,0			,AABBPoint	,0			}, // Point
	{0			,0			,AABBRay	,0			}, // Ray
	{AABBPoint	,AABBRay	,AABBAABB	,0			}, // Box
	{0			,0			,0			,0			}, // Circle
};