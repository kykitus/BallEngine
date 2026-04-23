#include "Globals.h"


// SYSTEM MACRO PANEL


Vector2f Globals_List::get_RectSize() { return RectSize; }
void Globals_List::set_RectSize(Vector2f val) { RectSize = val; }

float Globals_List::get_MinShapeDistance() { return MinShapeDistance; }
void Globals_List::set_MinShapeDistance(float val) { MinShapeDistance = val; }
Vector2f Globals_List::get_MaxSpeed() { return MaxSpeed; }
void Globals_List::set_MaxSpeed(Vector2f val) { MaxSpeed = val; }

// 

Globals_List Globals;
