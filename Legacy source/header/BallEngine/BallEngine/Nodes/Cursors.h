#ifndef SDL_ENGINE_CURSORS
#define SDL_ENGINE_CURSORS

#include "BallEngine/Nodes/Actor.h"


class DebugCursor : public Actor
{
public:
	
	Node& get_Seen();
	void set_Seen(Node* val);
	Node& get_Selected();
	void set_Selected(Node* val);



	virtual void check_Collision();

	void mouse_Left();
	void mouse_Right();
	void mouse_Middle();
	void mouse_ScrollFront();
	void mouse_ScrollBack();

	virtual void process_delta() override;


	DebugCursor(uint8_t parent, Vector2f pos, Vector2f length);

	DebugCursor() = default;
	~DebugCursor() = default;

protected:

	Node* Seen; // currently seen object
	Node* Selected; // Object that is seen independently from the position of the cursor;

};

#endif
