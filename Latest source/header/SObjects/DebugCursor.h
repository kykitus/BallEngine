#ifndef GAR_CURSOR
#define GAR_CURSOR

#include "SphereCore.h"
#include "Types/Collision.h"
#include "Types/CollisionShapes/Point.h"

class DebugCursor : public Effigy
{
public:
	 
	virtual void Tick();
	virtual void Physics();

	virtual void set_Position(Vector2f val);

	void Collides(CollidingShape* col, Hit* hit);

	DebugCursor();
	~DebugCursor();

	Dot* get_Body();

private:

	Dot* Body;

};

#endif