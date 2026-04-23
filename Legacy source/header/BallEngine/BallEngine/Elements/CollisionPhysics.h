#ifndef SDL_ENGINE_COLLISION_PHYSICS
#define SDL_ENGINE_COLLISION_PHYSICS

#include "BallEngine/Types.h"


typedef Hit(*IntersectFunction)(Colliding_Shape*, Colliding_Shape*);

struct Hit 
{
	Colliding_Shape* Collider;
	Vector2f Position;
	Vector2f Depth;
	Vector2f Normal;
	float time;

	Hit();
	Hit(Colliding_Shape* col, Vector2f pos, Vector2f overlap, Vector2f direction, float length);
};

struct Sweep 
{
	Hit Point;
	Vector2f Position;
	float time;

	Sweep() = default;
	Sweep(Hit hit, Vector2f pos, float length);
};



// SHAPES

class Colliding_Shape 
{
public:
	virtual Vector2f get_MinMaxX();
	virtual Vector2f get_MinMaxY();
	virtual Vector2f get_Center();
	const int get_Complexity();

	Node& get_Owner();
	void set_Owner(Node& val);
	void set_HashBelonging(std::pair<std::vector<int>, std::vector<int>> val);
	std::pair<std::vector<int>, std::vector<int>> get_HashBelonging();

	Colliding_Shape() = default;
	Colliding_Shape(Node& val);

protected:

	Node* Owner;
	std::pair<std::vector<int>, std::vector<int>> HashBelonging;
	int complexity;

};

class AABB : public Colliding_Shape 
{
public:
	GPU_Rect& get_Rect();
	Vector2f get_Position();
	void set_Position(Vector2f val);
	void add_Position(Vector2f val);
	void set_Size(Vector2f val);

	Vector2f get_MinMaxX();
	Vector2f get_MinMaxY();
	Vector2f get_Center();
	void set_Center(Vector2f val);
	Vector2f get_HalfSize();

	AABB() = default;
	AABB(Vector2f pos, Vector2f size, Node& val);

	void destructor(Mask& parent);
protected:

	GPU_Rect Rect = { 0, 0, 100, 100 }; // its X n Y lies in the up-left corner
};

//



Hit AABBPoint(Colliding_Shape* colA, Colliding_Shape* colB);

Hit AABBRay(Colliding_Shape* colA, Colliding_Shape* colB);
Hit AABBAABB(Colliding_Shape* colA, Colliding_Shape* colB);
Hit AABBCircle(Colliding_Shape* colA, Colliding_Shape* colB);


Hit CircleCircle(Colliding_Shape* colA, Colliding_Shape* colB);







extern IntersectFunction Intersection[4][4];

#endif