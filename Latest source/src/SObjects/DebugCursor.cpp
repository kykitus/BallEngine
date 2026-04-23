#include "SObjects/DebugCursor.h"



void DebugCursor::Tick()
{
}

void DebugCursor::Physics()
{

}

void DebugCursor::set_Position(Vector2f val)
{
	Body->set_Position(val);
}

void DebugCursor::Collides(CollidingShape* col, Hit* hit)
{
	Root->get_Logger()->push_Log("Mouse collides with button..... YAY");
}

DebugCursor::DebugCursor()
{
	Body = new Dot({ 0.0f, 0.0f }, *this);
	Body->get_Alarm_Collides().add_Listener(std::bind(&DebugCursor::Collides, this, std::placeholders::_1, std::placeholders::_2), this);
}

DebugCursor::~DebugCursor()
{
	delete Body;
}

Dot* DebugCursor::get_Body() { return Body; }
