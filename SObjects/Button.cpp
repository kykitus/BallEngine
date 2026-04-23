#include "SObjects/Button.h"

#include "Types/CollisionShapes/AABB.h"

#include "SphereCore.h"


void GAR_Button::Tick()
{
	Img.print();
}

void GAR_Button::Collides(CollidingShape* obj, Hit* hitdata)
{
	Img.set_Modulation({255,255,255,100});
}

GAR_Button::GAR_Button()
{
	Body = new AABB();
}

GAR_Button::GAR_Button(Vector2f pos)
{
	Img.set_Body(pos, {400,400});
	Img.load("Resources/Image/button.png");

	Body = new AABB(pos, { 400.0f, 400.0f }, *this);
	Body->set_HashBelonging({ { 1 }, { 1 } });

	Body->get_Alarm_Poked().add_Listener(std::bind(&GAR_Button::Collides, this, std::placeholders::_1, std::placeholders::_2), this);
}

GAR_Button::~GAR_Button()
{
	delete Body;
}

AABB* GAR_Button::get_Body() { return Body; }
