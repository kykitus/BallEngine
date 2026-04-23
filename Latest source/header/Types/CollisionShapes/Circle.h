#ifndef BE_CIRCLE
#define BE_CIRCLE

#include "Types/Collision.h"

class Circle : public CollidingShape 
{
public:



	Vector2f get_MinMaxX();
	Vector2f get_MinMaxY();
	Vector2f get_Center();


	Circle() = default;
	Circle(Vector2f pos, float radius, Effigy& val);

	Vector2f& get_Position();
	void set_Position(Vector2f pos);
	void add_Position(Vector2f pos);
	float& get_Radius();

protected:

	Vector2f Position = { 0, 0 };
	float Radius = 1.0f;
};

#endif
