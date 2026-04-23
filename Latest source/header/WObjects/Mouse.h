#ifndef BE_MOUSE
#define BE_MOUSE

#include <SDL3/SDL.h>

#include "Types/Vectors.h"
#include "WObjects/Keyboard.h"
#include "WObjects/Effigy.h"
#include "Types/Numbers.h"

class ENGN_Mouse : ENGN_Keyboard
{
public:

	void init(Effigy* cursor = nullptr);

	void refresh(SDL_Event* event) override;
	void read_Input(SDL_Event* event);

	ENGN_Mouse();

	Vector2f& get_Position();
	void set_Position(Vector2i pos);
	Effigy& get_Cursor();
	void set_Cursor(Effigy* val);
	Vector2f& get_CursorOffset();
	void set_CursorOffset(Vector2f val);
	int& get_WheelDirection();
	void set_WheelDirection(int val);
	bool get_IsMoving();
	void set_IsMoving(bool val);
	bool get_IsHoldingAKey();
	void set_IsHoldingAKey(bool val);

private:

	Vector2f Position;
	int WheelDirection = ZERO;
	Uint32 KeyEvent = 0;

	std::vector<int> ActionQueue = {};

	Effigy* Cursor; // Always set Cursor
	Vector2f CursorOffset = { 0.0f, 0.0f };

	std::shared_ptr<Effigy> BackCursor;


	bool IsMoving = false;
	bool IsHoldingAKey = false;


};

#endif
