#ifndef SDL_ENGINE_ROOT_MACRO_PANEL
#define SDL_ENGINE_ROOT_MACRO_PANEL

#include "BallEngine/Types.h"

// SYSTEM MACRO PANEL

class System_Macro_Panel
{
public:

	Vector2i get_ScreenSize();
	void set_Screensize(Vector2i val);
	std::string get_EnginePath();
	void set_EnginePath(std::string val);

	Vector2f get_RectSize();
	void set_RectSize(Vector2f val);

	float get_MinShapeDistance();
	void set_MinShapeDistance(float val);
	Vector2f get_MaxSpeed();
	void set_MaxSpeed(Vector2f val);

private:

	// App

	Vector2i ScreenSize = { 1280, 720 };
	std::string EnginePath = "header/BallEngine";

	// Shapes

	Vector2f RectSize = { 80.0f, 80.0f };

	// Physics

	float MinShapeDistance = 0.01f;

	Vector2f MaxSpeed = { 150.0f, 150.0f };

};

//

#endif