#include "BallEngine/Nodes/Actor.h"
#include "BallEngine/EngineCore.h"
#include "BallEngine/DataStructures/DataStructures.h"
#include "BallEngine/DataStructures/ResourceRepositiory.h"




///// ACTOR

Speed_Component_Base& Actor::get_Speed() { return Speed; }
Rectangle_Component& Actor::get_Body() { return Body; }
Collision_Autonomic& Actor::get_SuperBody() { return SuperBody; }
Visual_Component_Rect& Actor::get_Canva() { return Canva; }

void Actor::move_Hash()
{

	Speed.Velocity += Speed.Force / Speed.Mass * Root->get_Delta();

	Speed.Velocity = { std::clamp(Speed.Velocity.x, -Speed.MaxSpeed.x, Speed.MaxSpeed.x), std::clamp(Speed.Velocity.y, -Speed.MaxSpeed.y, Speed.MaxSpeed.y) };

	add_Position(Speed.Velocity * Speed.Direction * Root->get_Delta());

	Hit rePosition;
	for (int key : Body.get_Box().get_HashBelonging().second)
	{
		if (get_Mask().get_HashMap().check_HashMapCell(key))
		{
			for (Colliding_Shape* obj : get_Mask().get_HashMap().get_HashMapCell(key))
			{
				if (obj != &Body.get_Box() || obj != nullptr)
				{
					rePosition = Hit(Intersection[Body.get_Box().get_Complexity()][obj->get_Complexity()](&Body.pass_Shape(), obj));
					Body.get_Box().add_Position(rePosition.Depth * -1.0f);
					Position = Body.get_Box().get_Position();
				}
			}
		}
	}


	if (Speed.Velocity.x != 0 || Speed.Velocity.y != 0)
	{
		refresh_Position();
	}
}

void Actor::set_Position(Vector2f val)
{
	Position = val;
	Body.get_Box().set_Position(val);
	Canva.get_Plane().x = val.x;
	Canva.get_Plane().x = val.x;
	refresh_Position();
}
void Actor::add_Position(Vector2f val)
{
	Position += val;
	Body.get_Box().set_Position(Position);
	Canva.get_Plane().x += val.x;
	Canva.get_Plane().x += val.x;
	refresh_Position();
}

void Actor::refresh_Position()
{
	get_Mask().get_HashMap().flush(&Body.get_Box(), Body.get_Box().get_HashBelonging().first);
	Body.get_Box().set_HashBelonging
	(
		get_Mask().get_HashMap().where
		(
			&Body.pass_Shape(),
			SuperBody.get_CollisionMap().get_CollisionLayers(),
			SuperBody.get_CollisionMap().get_CollisionMasks()
			)
	);
}

void Actor::process_delta()
{
	if (!IsStatic || !IsAsleep) {
		force_move();
		Speed.damp_Velocity();
		Speed.stop_Force();
	}
}

void Actor::render()
{
	Canva.relate_to_Camera(this);
	GPU_BlitRect(Canva.get_Texture(), NULL, &Root->get_Renderer(), &Canva.get_Plane());
	
}


Actor::Actor(uint8_t parent) :
	Node(parent),
	Body(Position, MacroPanel.get_RectSize(), {1}, {1}, get_Mask(), * this),
	SuperBody(&Body, { {1}, {1} })
{

	Canva.set_TexturePath(std::string(MacroPanel.get_EnginePath()) + "/Textures/placeholder.png");
	Canva.set_Texture(get_Mask().get_TextureRep().request(Canva.get_TexturePath()));

	Canva.set_Plane(Position, MacroPanel.get_RectSize());
	set_Position({ 0.0f, 0.0f });
	Speed.MaxSpeed = MacroPanel.get_MaxSpeed();

}

Actor::Actor(uint8_t parent, Vector2f pos) :
	Node(parent),
	Body(pos, MacroPanel.get_RectSize(), { 1 }, { 1 }, get_Mask(), * this),
	SuperBody(&Body, { { 1 }, { 1 } })
{

	Canva.set_TexturePath(std::string(MacroPanel.get_EnginePath()) + "/Textures/placeholder.png");
	Canva.set_Texture(get_Mask().get_TextureRep().request(Canva.get_TexturePath()));

	Position = pos;
	Canva.set_Plane(Position, MacroPanel.get_RectSize());
	set_Position(pos);
	Speed.MaxSpeed = MacroPanel.get_MaxSpeed();

}

Actor::Actor(uint8_t parent, Vector2f pos, Vector2f size) : 
	Node(parent), 
	Body(pos, size, { 1 }, { 1 }, get_Mask(), * this),
	SuperBody(&Body, { { 1 }, { 1 } })
{

	Canva.set_TexturePath(std::string(MacroPanel.get_EnginePath()) + "/Textures/placeholder.png");
	Canva.set_Texture(get_Mask().get_TextureRep().request(Canva.get_TexturePath()));

	Position = pos;
	Canva.set_Plane(pos, size);
	set_Position(pos);
	Speed.MaxSpeed = MacroPanel.get_MaxSpeed();

}

//



//

void DebugActor::control_UP()
{
	Speed.Force.y -= 2300.0f;
}
void DebugActor::control_DOWN()
{
	Speed.Force.y += 2300.0f;
}
void DebugActor::control_LEFT()
{
	Speed.Force.x -= 2300.0f;
}
void DebugActor::control_RIGHT()
{
	Speed.Force.x += 2300.0f;
}
void DebugActor::control_INCREMENTER_7()
{
	Root->get_FPSLimit() += 1;
	Root->refresh_FPS();
}
void DebugActor::control_DECREMENTER_4()
{
	Root->get_FPSLimit() -= 1;
	Root->refresh_FPS();
}

DebugActor::DebugActor(uint8_t parent) : 
	Node(parent),
	Actor(parent){}
DebugActor::DebugActor(uint8_t parent, Vector2f pos) : Node(parent), Actor(parent, pos){}
DebugActor::DebugActor(uint8_t parent, Vector2f pos, Vector2f size) : Node(parent), Actor(parent, pos, size){}
