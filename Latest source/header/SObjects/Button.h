#ifndef GAR_BUTTON
#define GAR_BUTTON


#include "Types/Collision.h"
#include "WObjects/Effigy.h"
#include "Types/Assets/Image.h"

class GAR_Button : public Effigy
{
public:

	virtual void Tick();

	void Collides(CollidingShape* obj, Hit* hitdata);

	GAR_Button();
	GAR_Button(Vector2f pos);
	~GAR_Button();

	AABB* get_Body();

private:

	Image Img;
	AABB* Body;

};

#endif
