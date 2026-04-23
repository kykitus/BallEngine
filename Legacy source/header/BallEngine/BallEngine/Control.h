#ifndef PACMAN_CONTROL
#define PACMAN_CONTROL

#include "BallEngine/Types.h"
#include "BallEngine/Elements/Func.h"

enum my_mouse_controls
{
	MOUSE_LEFT_C = 1,
	MOUSE_RIGHT_C = 4,
	MOUSE_MID_C = 2,
};

// CONTROLLER

class Keyboard
{
public:

	void set_Key(short int address, int key);
	short int get_Key(short int address); //if no values, returns whole array
	bool get_Input(unsigned int key_index);
	void refresh(Mask* Target);
	Keyboard() = default;

private:

	const Uint8* KeyEvent = SDL_GetKeyboardState(NULL);
	int ControllerKeys[20] =
	{
		SDL_SCANCODE_W, // Negative Y (UP)
		SDL_SCANCODE_S, // Positive Y (DOWN)
		SDL_SCANCODE_A, // Negative X (LEFT)
		SDL_SCANCODE_D, // Positive X (RIGHT)
		SDL_SCANCODE_KP_7,
		SDL_SCANCODE_KP_4,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	};

};

class Mouse
{
public:

	void print_Cords();

	void refresh_Mouse();
	void refresh_Cursor();

	void read_Input();

	Vector2i get_Position();
	void set_Position(Vector2i val);
	Node& get_Cursor();
	void set_Cursor(Node* val);
	Vector2f get_CursorOffset();
	void set_CursorOffset(Vector2f val);
	int get_WheelDirection();
	void set_WheelDirection(int val);
	void add_ActionQueue(int val);
	bool get_IsMoving();
	void set_IsMoving(bool val);
	bool get_IsHoldingAKey();
	void set_IsHoldingAKey(bool val);

	Mouse();

private:

	Vector2i Position = { 0, 0 };
	int WheelDirection = ZERO;

	Uint32 KeyEvent = 0;

	std::unordered_map<int, int> ControllerKeys;

	std::vector<int> ActionQueue = {};

	Node* Cursor;
	Vector2f CursorOffset = { 0.0f, 0.0f };


	bool IsMoving = false;
	bool IsHoldingAKey = false;

};

class Input
{
public:

	FuncBase& get_Key(int id);
	void replace_Key(FuncBase* key, int id);
	void use_Key(int id, Node* caller);

	void flush();

private:

	std::array<FuncBase*, 20> Keys;

};

#endif