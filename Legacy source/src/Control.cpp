#include "BallEngine/Control.h"
#include "BallEngine/EngineCore.h"


void Keyboard::set_Key(short int address, int key)
{
	ControllerKeys[address] = key;
}

short int Keyboard::get_Key(short int address = 0)
{
	return ControllerKeys[address];
}

bool Keyboard::get_Input(unsigned int key_index)
{
	return KeyEvent[ControllerKeys[key_index]];
}

void Keyboard::refresh(Mask* Target)
{
	for (int key = 0; key < 20; key++) { if (KeyEvent[ControllerKeys[key]]) { Target->control_call(key); } }
}

//

void Mouse::print_Cords() { refresh_Mouse(); system("CLS"); PRINT "|| " << WheelDirection << " ||"; }

void Mouse::refresh_Mouse()
{
	KeyEvent = SDL_GetMouseState(&Position.x, &Position.y);
}

void Mouse::refresh_Cursor()
{
	if (Cursor != nullptr)
	{
		Cursor->set_Position({ Position + CursorOffset });
		read_Input();
		for (int index : ActionQueue) { Cursor->poke(ControllerKeys[index], *Cursor); }
	}
	ActionQueue = {};
}

void Mouse::read_Input()
{
	int num = KeyEvent;
	int counter = 0;

	while (num != 0)
	{
		if (num % 2 == 1) { ActionQueue.push_back(counter); }
		num /= 2;
		counter++;
	}
}

Vector2i Mouse::get_Position() { return Position; }
void Mouse::set_Position(Vector2i val) { Position = val; }
Node& Mouse::get_Cursor() { return *Cursor; }
void Mouse::set_Cursor(Node* val) { Cursor = val; }
Vector2f Mouse::get_CursorOffset() { return CursorOffset; }
void Mouse::set_CursorOffset(Vector2f val) { CursorOffset = val; }
int Mouse::get_WheelDirection() { return WheelDirection; }
void Mouse::set_WheelDirection(int val) { WheelDirection = val; }
void Mouse::add_ActionQueue(int val) { ActionQueue.push_back(val); }
bool Mouse::get_IsMoving() { return IsMoving; }
void Mouse::set_IsMoving(bool val) { IsMoving = val; }
bool Mouse::get_IsHoldingAKey() { return IsHoldingAKey; }
void Mouse::set_IsHoldingAKey(bool val) { IsHoldingAKey = val; }

Mouse::Mouse()
{
	ControllerKeys[0] = MOUSE_LC;
	ControllerKeys[1] = MOUSE_MB;
	ControllerKeys[2] = MOUSE_RC;
	ControllerKeys[-1] = MOUSE_SF;
	ControllerKeys[-2] = MOUSE_SB;
}

//



//

FuncBase& Input::get_Key(int id) { return *Keys[id]; }
void Input::replace_Key(FuncBase* key, int id) { Keys[id] = key; }
void Input::use_Key(int id, Node* caller = nullptr) { Keys[id]->use(caller); }

void Input::flush() { for (FuncBase* fun : Keys) { fun = nullptr; } }