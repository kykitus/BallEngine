#include "WObjects/Effigy.h"

#include <iostream>

#include "Types/Macros.h"



Vector2f& Effigy::get_Position() { return Position; }
void Effigy::set_Position(Vector2f val) { Position = val; }


Effigy::~Effigy()
{

	//Interaction.clear();
	/*for (auto& [key, val] : Interaction)
	{
		val = nullptr;
	}*/
}
