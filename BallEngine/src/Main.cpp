#define SDL_MAIN_HANDLED

#include "BallEngine/Global.h"
#include "BallEngine/EngineCore.h"


int main() 
{
	create_Game(new Game());
	Root->Main();
}