#ifndef BE_POINT
#define BE_POINT

#include "Types/Collision.h"

class Dot : public CollidingShape
{
public:

	virtual Vector2f get_MinMaxX();
	virtual Vector2f get_MinMaxY();
	virtual Vector2f get_Center();

	Vector2f& get_Position();
	void set_Position(Vector2f val);
	void add_Position(Vector2f val);

	Dot() = default;
	Dot(Vector2f pos, Effigy& val);


protected:

	Vector2f Position = { 0, 0 };

};

#endif
