#ifndef BE_AABB
#define BE_AABB

#include "Types/Collision.h"

class AABB : public CollidingShape
{
public:
	SDL_FRect& get_Rect();
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
	AABB(Vector2f pos, Vector2f size, Effigy& val);


protected:

	SDL_FRect Rect = { 0, 0, 100, 100 }; // its X n Y lies in the up-left corner
};


#endif
