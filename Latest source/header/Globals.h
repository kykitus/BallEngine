#ifndef BE_GLOBALS
#define BE_GLOBALS

#include <string>

#include "Types/Vectors.h"

class Globals_List
{
public:

	Vector2f get_RectSize();
	void set_RectSize(Vector2f val);

	float get_MinShapeDistance();
	void set_MinShapeDistance(float val);
	Vector2f get_MaxSpeed();
	void set_MaxSpeed(Vector2f val);

private:


	// Shapes

	Vector2f RectSize = { 80.0f, 80.0f };

	// Physics

	float MinShapeDistance = 0.01f;

	Vector2f MaxSpeed = { 150.0f, 150.0f };

};

extern Globals_List Globals;

#endif
