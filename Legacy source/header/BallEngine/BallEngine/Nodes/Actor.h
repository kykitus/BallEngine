#ifndef SDL_ENGINE_ACTOR
#define SDL_ENGINE_ACTOR

#include "BallEngine/Nodes/Nodes.h"
#include "BallEngine/Components/BasicComponents.h"
#include "BallEngine/Elements/Func.h"

// ACTOR VISUAL COMPONENT

//



// ACTOR

class Actor : public Effigy
{
public:

	Speed_Component_Base& get_Speed();
	Rectangle_Component& get_Body();
	Collision_Autonomic& get_SuperBody();
	Visual_Component_Rect& get_Canva();

	virtual void set_Position(Vector2f val) override;
	void add_Position(Vector2f val);

	virtual void refresh_Position();

	virtual void move_Hash();

	std::function<void()> force_move = std::bind(&Actor::move_Hash, this);

	virtual void process_delta() override;
	virtual void render() override;

	Actor(uint8_t parent);
	Actor(uint8_t parent, Vector2f pos);
	Actor(uint8_t parent, Vector2f pos, Vector2f size);

	virtual ~Actor() = default;

protected:

	Speed_Component_Base Speed;
	Rectangle_Component Body;
	Collision_Autonomic SuperBody;
	Visual_Component_Rect Canva;

};

//

class DebugActor : public Actor
{
public:
	using Actor::Actor;

	virtual void control_UP();
	virtual void control_DOWN();
	virtual void control_LEFT();
	virtual void control_RIGHT();
	virtual void control_INCREMENTER_7();
	virtual void control_DECREMENTER_4();

	std::unique_ptr<FuncBase> Control[6] =
	{
		std::unique_ptr<Func<FNormal>>(new Func<FNormal>(std::bind(&DebugActor::control_UP, this), this)),
		std::unique_ptr<Func<FNormal>>(new Func<FNormal>(std::bind(&DebugActor::control_DOWN, this), this)),
		std::unique_ptr<Func<FNormal>>(new Func<FNormal>(std::bind(&DebugActor::control_LEFT, this), this)),
		std::unique_ptr<Func<FNormal>>(new Func<FNormal>(std::bind(&DebugActor::control_RIGHT, this), this)),
		std::unique_ptr<Func<FSingle>>(new Func<FSingle>(std::bind(&DebugActor::control_INCREMENTER_7, this), this)),
		std::unique_ptr<Func<FNormal>>(new Func<FNormal>(std::bind(&DebugActor::control_DECREMENTER_4, this), this)),
	};

	DebugActor(uint8_t parent);
	DebugActor(uint8_t parent, Vector2f pos);
	DebugActor(uint8_t parent, Vector2f pos, Vector2f size);
};
	

#endif