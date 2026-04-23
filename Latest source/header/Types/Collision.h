#ifndef BE_COLLISION
#define BE_COLLISION

#include <SDL3/SDL_rect.h>

#include "WObjects/Effigy.h"
#include "Types/Delegate.h"


enum shape_complexity
{
	DOT,
	RAY,
	BOX,
	CIRCLE,
	CONVEX
};

struct Hit;
struct Sweep;
class CollidingShape;
class Dot;
class Ray;
class AABB;
class Circle;

typedef Hit(*IntersectFunction)(CollidingShape*, CollidingShape*);

struct Hit
{
	CollidingShape* Collider;
	Vector2f Position;
	Vector2f Depth;
	Vector2f Normal;
	float time;

	Hit();
	Hit(CollidingShape* col, Vector2f pos, Vector2f overlap, Vector2f direction, float length);
};

struct Sweep
{
	Hit Dot;
	Vector2f Position;
	float time;

	Sweep() = default;
	Sweep(Hit hit, Vector2f pos, float length);
};



// SHAPES

class CollidingShape
{
public:
	virtual Vector2f get_MinMaxX();
	virtual Vector2f get_MinMaxY();
	virtual Vector2f get_Center();


	AlarmWA<CollidingShape*, Hit*>& get_Alarm_Collides();
	AlarmWA<CollidingShape*, Hit*>& get_Alarm_Poked();


	void set_Owner(Effigy& val);
	void set_HashBelonging(std::pair<std::vector<int>, std::vector<int>> val);
	std::pair<std::vector<int>, std::vector<int>> get_HashBelonging();
	void check_Collision();

	CollidingShape();
	CollidingShape(Effigy& val);

	Effigy& get_Owner();
	const int get_Complexity();
	uint64_t get_UID() const;

protected:

	void setup();

	AlarmWA<CollidingShape*, Hit*> Collides;
	AlarmWA<CollidingShape*, Hit*> Poked;

	Effigy* Owner;
	std::pair<std::vector<int>, std::vector<int>> HashBelonging;
	int Complexity;
	uint64_t UID;

};

//
// Functions with "//" sign are relevant. The rest just switch A and B with place and forward them to relevant functions
//

Hit PointPoint(CollidingShape* colA, CollidingShape* colB); //
Hit PointRay(CollidingShape* colA, CollidingShape* colB); //
Hit PointAABB(CollidingShape* colA, CollidingShape* colB); //
Hit PointCircle(CollidingShape* colA, CollidingShape* colB); //

Hit RayPoint(CollidingShape* colA, CollidingShape* colB); 
Hit RayRay(CollidingShape* colA, CollidingShape* colB); //
Hit RayAABB(CollidingShape* colA, CollidingShape* colB); //
Hit RayCircle(CollidingShape* colA, CollidingShape* colB); //

Hit AABBPoint(CollidingShape* colA, CollidingShape* colB);
Hit AABBRay(CollidingShape* colA, CollidingShape* colB);
Hit AABBAABB(CollidingShape* colA, CollidingShape* colB); //
Hit AABBCircle(CollidingShape* colA, CollidingShape* colB); //

Hit CirclePoint(CollidingShape* colA, CollidingShape* colB);
Hit CircleRay(CollidingShape* colA, CollidingShape* colB);
Hit CircleAABB(CollidingShape* colA, CollidingShape* colB);
Hit CircleCircle(CollidingShape* colA, CollidingShape* colB); //








extern IntersectFunction Intersection[4][4];

#endif