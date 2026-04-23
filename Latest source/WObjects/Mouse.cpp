#include "WObjects/Mouse.h"
#include "SObjects/DebugCursor.h"

void ENGN_Mouse::init(Effigy* cursor)
{
	BackCursor = std::shared_ptr<Effigy>(new DebugCursor);
	if (cursor == nullptr) { Cursor = BackCursor.get(); }
	else { Cursor = cursor; }
}

void ENGN_Mouse::refresh(SDL_Event* event)
{
	KeyEvent = SDL_GetMouseState(&Position.x, &Position.y);
	Cursor->set_Position({ Position + CursorOffset });
}

void ENGN_Mouse::read_Input(SDL_Event* event)
{
	int num = KeyEvent;
	int counter = 0;

	while (num != 0)
	{
		if (num % 2 == 1) 
		{
			ActionQueue.push_back(counter);
			if (event->key.key == counter) { ListeningKeys[counter].emit(); }
		}
		num /= 2;
		counter++;
	}


	// Cursor

	if (Cursor != nullptr)
	{
		for (int index : ActionQueue) { Cursor->poke(index * -1, *Cursor); }
	}

}

ENGN_Mouse::ENGN_Mouse()
{
}

Vector2f& ENGN_Mouse::get_Position() { return Position; }
void ENGN_Mouse::set_Position(Vector2i val) { Position = val; }
Effigy& ENGN_Mouse::get_Cursor() { return *Cursor; }
void ENGN_Mouse::set_Cursor(Effigy* val) { Cursor = val; }
Vector2f& ENGN_Mouse::get_CursorOffset() { return CursorOffset; }
void ENGN_Mouse::set_CursorOffset(Vector2f val) { CursorOffset = val; }
int& ENGN_Mouse::get_WheelDirection() { return WheelDirection; }
void ENGN_Mouse::set_WheelDirection(int val) { WheelDirection = val; }
bool ENGN_Mouse::get_IsMoving() { return IsMoving; }
void ENGN_Mouse::set_IsMoving(bool val) { IsMoving = val; }
bool ENGN_Mouse::get_IsHoldingAKey() { return IsHoldingAKey; }
void ENGN_Mouse::set_IsHoldingAKey(bool val) { IsHoldingAKey = val; }