#include "BallEngine/Nodes/Cursors.h"
#include "BallEngine/EngineCore.h"
#include "BallEngine/DataStructures/DataStructures.h"

Node& DebugCursor::get_Seen() { return *Seen; }
void DebugCursor::set_Seen(Node* val) { Seen = val; }
Node& DebugCursor::get_Selected() { return *Selected; }
void DebugCursor::set_Selected(Node* val) { Selected = val; }

void DebugCursor::check_Collision()
{
	Seen = nullptr;

	Hit rePosition;
	for (int key : Body.get_Box().get_HashBelonging().second)
	{
		if (get_Mask().get_HashMap().check_HashMapCell(key))
		{
			for (Colliding_Shape* obj : get_Mask().get_HashMap().get_HashMapCell(key))
			{
				if (obj != &Body.get_Box() || obj != nullptr)
				{
					rePosition = Hit(Intersection[Body.get_Box().get_Complexity()][obj->get_Complexity()](&Body.pass_Shape(), obj));
					if (rePosition.Depth.x != 0 || rePosition.Depth.y != 0) { Seen = &obj->get_Owner(); }

				}
			}
		}
	}
}

void DebugCursor::mouse_Left() { if (Seen != nullptr) { Seen->poke(1, *this); } }
void DebugCursor::mouse_Right() { if (Seen != nullptr) { Seen->poke(2, *this); } }
void DebugCursor::mouse_Middle() { if (Seen != nullptr) { Seen->poke(3, *this); } }
void DebugCursor::mouse_ScrollFront() { if (Seen != nullptr) { Seen->poke(4, *this); } }
void DebugCursor::mouse_ScrollBack() { if (Seen != nullptr) { Seen->poke(5, *this); } }

void DebugCursor::process_delta()
{
	if (!IsStatic || !IsAsleep) {
		check_Collision();
		refresh_Position();
	}

	//GPU_Rectangle2(&Root.get_Renderer(), Body.get_Box().get_Rect(),SDL_Color(255,0,0,255));
}

DebugCursor::DebugCursor(uint8_t parent, Vector2f pos, Vector2f length) : Node(parent), Actor(parent, pos, length)
{
	refresh_Position();
	Interaction[1] = std::bind(&DebugCursor::mouse_Left, this);
	Interaction[2] = std::bind(&DebugCursor::mouse_Middle, this);
	Interaction[3] = std::bind(&DebugCursor::mouse_Right, this);
	Interaction[4] = std::bind(&DebugCursor::mouse_ScrollFront, this);
	Interaction[5] = std::bind(&DebugCursor::mouse_ScrollBack, this);
}

