#ifndef BE_SPHERE_CORE
#define BE_SPHERE_CORE

#include <SDL3/SDL.h>

#include <map>

#include "WObjects/Keyboard.h"
#include "WObjects/Mouse.h"
#include "WObjects/Cog.h"
#include "WObjects/Effigy.h"
#include "Types/Vectors.h"
#include "Flags.h"
#include "WObjects/Logger.h"
#include "WObjects/SpatialHashMap.h"


class SphereCore 
{
public:

	void init();

	void start_Newbies();
	void Cog_Tick(Cog* obj);
	void listen_PhysicsTimer();
	void Cog_PhysicsTick(Cog* obj);
	void Render();

	template<typename T>
	T* init_Member(T* obj, Cog* parent, int render_layer)
	{
		std::shared_ptr<Cog> new_obj = std::shared_ptr<Cog>(obj);
		ReadyList.push_back(obj);
		if (parent != nullptr) { parent->add_Child(new_obj); }
		else { DrivingCog->add_Child(new_obj); }
		RenderList[render_layer].push_back(new_obj);

		return obj;
	}

	void Loop();

	void clear_Screen();

	void calculate_Delta();
	void listen_Loop();
	void refresh_FPS();

	SphereCore();
	~SphereCore();

	Cog& get_DrivingCog();

	ENGN_Keyboard* get_Keyboard();
	ENGN_Mouse* get_Mouse();
	ENGN_Logger* get_Logger();
	SpatialHashMap* get_CollisionMap();


	SDL_Window* get_Window();
	SDL_Renderer* get_Renderer();

	Vector2i& get_WindowSize();
	void set_WindowSize(Vector2i size);
	Vector2f& get_RenderScale();
	void set_RenderScale(Vector2f scale);

	const Uint64 get_Last();
	const double get_Delta();
	Vector2f& get_CameraMod();
	int& get_FPSLimit();


private:

	std::shared_ptr<Cog> DrivingCog;
	std::map<int, std::vector<std::shared_ptr<Cog>>> RenderList;
	std::vector<Cog*> ReadyList;

	// Parts

	ENGN_Keyboard* Keyboard;
	ENGN_Mouse* Mouse;

	ENGN_Logger* Logger;

	SpatialHashMap* CollisionMap;

	//


	SDL_Window* Window = NULL;
	SDL_Renderer* Renderer = NULL;

	Vector2i WindowSize;
	Vector2i DrawableSize;
	Vector2f RenderScale = { 1.0f, 1.0f };

	Uint64 Last = SDL_GetPerformanceCounter();
	int Timer = 0;
	double Delta = 0; 
	int FPSLimit = 60;
	double FrameDelay = 0;
	double FrameDelayCounter = 0;
	double PhysicsDelay = 0;

	int FrameCounter = 0;

	Vector2f CameraMod = { 0.0f,0.0f };

};

extern SphereCore* Root;

#endif
