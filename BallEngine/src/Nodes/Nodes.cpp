#include "BallEngine/Nodes/Nodes.h"
#include "BallEngine/Global.h"

#include "BallEngine/EngineCore.h"

// NODE

void Node::process_delta() { PRINT "collision"; }
void Node::render() { PRINT "render"; }

void Node::poke(int val, Node& caller) { if (Interaction.count(val)) { Interaction[val](caller); } else { PRINT "No Function Called on poke(" << val << ")"; } }

bool Node::get_Sleep() { return IsAsleep; }
void Node::set_Sleep(bool val) { IsAsleep = val; }
Mask& Node::get_Mask() { return Root->get_Mask(ParentMask); }

Vector2f Node::get_Position() { return Position; }
void Node::set_Position(Vector2f val) { Position = val; }

Node::Node(uint8_t parent) : ParentMask(parent) {}

Node::~Node() 
{

	//Interaction.clear();
	/*for (auto& [key, val] : Interaction) 
	{
		val = nullptr;
	}*/
}

//

// EFFIGY

bool Effigy::get_IsVisible() { return IsVisible; }
void Effigy::set_IsVisible(bool val) { IsVisible = val; }

void Effigy::render() { PRINT "render"; }

//