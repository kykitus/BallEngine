#include "BallEngine/DataStructures/RootMacroPanel.h"

// SYSTEM MACRO PANEL

Vector2i System_Macro_Panel::get_ScreenSize() { return ScreenSize; }
void System_Macro_Panel::set_Screensize(Vector2i val) { ScreenSize = val; }
std::string System_Macro_Panel::get_EnginePath() { return EnginePath; }
void System_Macro_Panel::set_EnginePath(std::string val) { EnginePath = val; }

Vector2f System_Macro_Panel::get_RectSize() { return RectSize; }
void System_Macro_Panel::set_RectSize(Vector2f val) { RectSize = val; }

float System_Macro_Panel::get_MinShapeDistance() { return MinShapeDistance; }
void System_Macro_Panel::set_MinShapeDistance(float val) { MinShapeDistance = val; }
Vector2f System_Macro_Panel::get_MaxSpeed() { return MaxSpeed; }
void System_Macro_Panel::set_MaxSpeed(Vector2f val) { MaxSpeed = val; }

// 