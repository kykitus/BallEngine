#ifndef PACMAN_CLASSES
#define PACMAN_CLASSES

#include "ExternalLibs.h"

#include <Windows.h>
#include <fstream>
#include <conio.h>
#include <functional>
#include <cmath>
#include <algorithm> 
#include <map>
#include <list>
#include <chrono>
#include <iostream>

#include "BallEngine/Debug.h"

enum Sign 
{
	NEGATIVE = -1,
	ZERO = 0,
	POSITIVE = 1
};

enum Poke_Type 
{
	COLLISION, // For example: collision force recoil, bullet hit 

	MOUSE_LC, // buttons, drag n drop
	MOUSE_RC,
	MOUSE_MB,
	MOUSE_SF,
	MOUSE_SB,

	CUSTOM_1, // For specific situations of your choice
	CUSTOM_2,
	CUSTOM_3,
	CUSTOM_4,
};

class Game;

class Input;
class Mask;

class Speed_Component_Base;

class Visual_Component_Base;
class Visual_Component_Array;
class TextBox;

class Collision_Component_Base;
class Rectangle_Component;
class Collision_Array_Base;

class CollisionPlane;
class COMInterface;

struct Hit;
struct Sweep;
class Colliding_Shape;
class AABB;

class Node;
class Effigy;

class Actor;
class DebugActor;

class Tile_Class;
class Tile;
class Colliding_Tile;
class Tile_Map;

class Spatial_Hash_Map;
class Texture_Repository;
class System_Macro_Panel;

class Control_Journal;
class Button_Entry;

class FuncBase;
class FNormal;
class FSingle;
template <class Type>
class Func;

class Controller;
class Keyboard;
class Mouse;

class DebugCursor;

struct Vector2f;
struct Vector2i;


#endif
