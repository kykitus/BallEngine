#include "Types/Collision.h"

#include <utility>
#include <vector>


#include "Types/Numbers.h"
#include "Globals.h"
#include "SphereCore.h"

#include "Types/CollisionShapes/Point.h"

#include "Types/CollisionShapes/AABB.h"
#include "Types/CollisionShapes/Circle.h"

Hit::Hit() :
	Collider(0),
	Position(0, 0),
	Depth(0, 0),
	Normal(0, 0),
	time(0)
{
}
Hit::Hit(CollidingShape* col, Vector2f pos, Vector2f overlap, Vector2f direction, float length) :
	Collider(col),
	Position(pos),
	Depth(overlap),
	Normal(direction),
	time(length)
{
}

Sweep::Sweep(Hit hit, Vector2f pos, float length) :
	Dot(hit),
	Position(pos),
	time(length)
{
}



// SHAPES

Vector2f CollidingShape::get_MinMaxX() { return { 0.0f, 0.0f }; }
Vector2f CollidingShape::get_MinMaxY() { return { 0.0f, 0.0f }; }

Vector2f CollidingShape::get_Center() { return { 0.0f, 0.0f }; }


AlarmWA<CollidingShape*, Hit*>& CollidingShape::get_Alarm_Collides() { return Collides; }
AlarmWA<CollidingShape*, Hit*>& CollidingShape::get_Alarm_Poked() { return Poked; }


void CollidingShape::set_Owner(Effigy& val) { Owner = &val; }
void CollidingShape::set_HashBelonging(std::pair<std::vector<int>, std::vector<int>> val) { HashBelonging = val; }
std::pair<std::vector<int>, std::vector<int>> CollidingShape::get_HashBelonging() { return HashBelonging; }

void CollidingShape::check_Collision()
{
	SpatialHashMap* map = Root->get_CollisionMap();
	Hit hitdata;
	for (int key : HashBelonging.second)
	{
		if (map->check_HashMapCell(key)) 
		{
			for (CollidingShape* col : map->get_HashMapCell(key)) 
			{
				if (col != this) 
				{
					hitdata = Hit(Intersection[get_Complexity()][col->get_Complexity()](this, col));
					if (hitdata.Collider != nullptr) { Collides.emit(&*col, &hitdata); col->get_Alarm_Poked().emit(this, &hitdata); }
				}
			}
		}
	}
}

CollidingShape::CollidingShape() { setup(); }
CollidingShape::CollidingShape(Effigy& val) : Owner(&val) { setup(); }

Effigy& CollidingShape::get_Owner() { return *Owner; }
const int CollidingShape::get_Complexity() { return Complexity; }
uint64_t CollidingShape::get_UID() const { return UID; }
void CollidingShape::setup() { UID = Root->get_CollisionMap()->rent_UID(); }

//



Hit PointPoint(CollidingShape* colA, CollidingShape* colB) 
{
	Dot* A = dynamic_cast<Dot*>(colA);
	Dot* B = dynamic_cast<Dot*>(colB);
	Vector2f apos = A->get_Position();
	if (A->get_Position() != A->get_Position()) { return Hit(); }
	return Hit
	(
		A,
		apos,
		{0, apos.y + Globals.get_MinShapeDistance()},
		{0.0f, -1.0f},
		0.0f
	);
}

Hit PointRay(CollidingShape* colA, CollidingShape* colB) { return Hit(); }
Hit PointAABB(CollidingShape* colA, CollidingShape* colB) 
{
	Dot* A = dynamic_cast<Dot*>(colA);
	AABB* B = dynamic_cast<AABB*>(colB);

	Vector2f apos = A->get_Position();

	Vector2f distance =
	{
		B->get_Center().x - apos.x,
		B->get_Center().y - apos.y
	};

	Vector2f penetration =
	{
		(B->get_HalfSize().x) - abs(distance.x),
		(B->get_HalfSize().y) - abs(distance.y)
	};
	if (penetration.x <= 0 || penetration.y <= 0) { return Hit(); }
	if (penetration.x < penetration.y)
	{
		int sign = sgn(distance.x);
		return Hit
		(
			A,
			{ apos.x, B->get_Center().y},
			{ (penetration.x + Globals.get_MinShapeDistance()) * sign, 0.0f },
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
			{ B->get_Center().x, apos.y },
			{ 0.0f, (penetration.y + Globals.get_MinShapeDistance()) * sign },
			{ 0.0f, (float)sign },
			0.0f
		);
	}

}
Hit PointCircle(CollidingShape* colA, CollidingShape* colB) { return Hit(); }

Hit RayPoint(CollidingShape* colA, CollidingShape* colB) { return PointRay(colB, colA); }
Hit RayRay(CollidingShape* colA, CollidingShape* colB) { return Hit(); }
Hit RayAABB(CollidingShape* colA, CollidingShape* colB) { return Hit(); }
Hit RayCircle(CollidingShape* colA, CollidingShape* colB) { return Hit(); }

Hit AABBPoint(CollidingShape* colA, CollidingShape* colB) { return PointAABB(colB, colA); }
Hit AABBRay(CollidingShape* colA, CollidingShape* colB) { return RayAABB(colB, colA); }
Hit AABBAABB(CollidingShape* colA, CollidingShape* colB)
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
			{ (penetration.x + Globals.get_MinShapeDistance()) * sign, 0.0f },
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
			{ 0.0f, (penetration.y + Globals.get_MinShapeDistance()) * sign },
			{ 0.0f, (float)sign },
			0.0f
		);
	}
}

Hit AABBCircle(CollidingShape* colA, CollidingShape* colB) { return Hit(); }

Hit CirclePoint(CollidingShape* colA, CollidingShape* colB) { return PointCircle(colB, colA); }
Hit CircleRay(CollidingShape* colA, CollidingShape* colB) { return RayCircle(colB, colA); }
Hit CircleAABB(CollidingShape* colA, CollidingShape* colB) { return AABBCircle(colB, colA); }
Hit CircleCircle(CollidingShape* colA, CollidingShape* colB) 
{
	Circle* A = dynamic_cast<Circle*>(colA);
	Circle* B = dynamic_cast<Circle*>(colB);
	Vector2f apos = A->get_Position();
	Vector2f bpos = B->get_Position();

	Vector2f distance = bpos - apos;
	Vector2f penetration =
	{
		(A->get_Radius() + B->get_Radius()) - abs(distance.x),
		(A->get_Radius() + B->get_Radius()) - abs(distance.y)
	};
	if (penetration.x <= 0, penetration.y <= 0) { return Hit(); }

	Vector2f direction = Vector2f{ bpos - apos }.normalised();

	return Hit
	(
		A,
		apos + direction * A->get_Radius(),
		{ penetration * direction },
		{ direction },
		0.0f
	);
}



IntersectFunction Intersection[4][4] =
{ //Dot			Ray			Box			Circle
	{PointPoint,	PointRay,	PointAABB,	PointCircle	}, // Dot
	{RayPoint,		RayRay,		RayAABB,	RayCircle	}, // Ray
	{AABBPoint,		AABBRay,	AABBAABB,	AABBCircle	}, // Box
	{CirclePoint,	CircleRay,	CircleAABB,	CircleCircle}, // Circle
};