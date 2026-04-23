#ifndef PACMAN_MAINLOOP
#define PACMAN_MAINLOOP

#include "BallEngine/DataStructures/RootMacroPanel.h"
#include "BallEngine/Global.h"
#include "BallEngine/Control.h"
#include "Nodes/Nodes.h"
#include "BallEngine/DataStructures/ControlJournal.h"
#include "BallEngine/DataStructures/DataStructures.h"
#include "BallEngine/DataStructures/ResourceRepositiory.h"


enum simulation_flags 
{
	S_SLEEP,      // default sleep
	S_VISIBLE,    // default visible

	REQ_CONTROLS,
	REQ_UPDATE,
	REQ_HASH_MAP,
	REQ_RENDER,
	REQ_TEXTURE_REP
};

class Mask
{
public:

	bool get_Sleep();
	void set_Sleep(bool val);
	bool get_Visible();
	void set_Visible(bool val);
	bool get_HaveControls();
	void set_HaveControls(bool val);
	bool get_HaveHash();
	void set_HaveHash(bool val);
	bool get_HaveTextureRep();
	void set_HaveTextureRep(bool val);
	bool get_HaveActionReg();
	void set_HaveActionReg(bool val);

	std::map<int, std::vector<std::shared_ptr<Node>>>& get_Nodes();

	Input& get_Input();
	Spatial_Hash_Map& get_HashMap();
	Texture_Repository& get_TextureRep();
	Control_Journal& get_ActionReg();

	void control_call(int num);


	void do_Sequence();

	// Sequence functions
	void update();
	void render();

	//

	void clear_Lists();

	Mask();
	Mask(std::vector<bool> flags); // priority can be only -1 for background mask, or 1 for foreground 

	template<typename T>
	T* init_Member(T* obj, int update_priority, int render_priority, bool update, bool render)
	{
		std::shared_ptr<Node> new_obj = std::shared_ptr<Node>(obj);
		if (update) { UpdateList[update_priority].push_back(new_obj); }
		if (render) { RenderList[update_priority].push_back(new_obj); }

		return obj;
	}

private:

	bool IsAsleep;
	bool IsVisible;
	bool HaveControls;
	bool HaveHash;
	bool HaveTextureRep;
	bool HaveActionReg;

	std::unique_ptr<Input> Controls;
	std::unique_ptr<Spatial_Hash_Map> HashMap;
	std::unique_ptr<Texture_Repository> TextureRep;
	std::unique_ptr<Control_Journal> ActionRegistry;

	std::map<int, std::vector<std::shared_ptr<Node>>> UpdateList;
	std::map<int, std::vector<std::shared_ptr<Node>>> RenderList;

	std::vector<var_func> Sequence;

};

class Controller 
{
public:

	Mask& get_Focus();
	void set_Focus(Mask& val);
	Keyboard& get_Keyboard();
	Mouse& get_Mouse();

	void refresh();

private:

	Keyboard Keys;
	Mouse Points;

	Mask* Focus;

};

class Game
{
public:
	void Init();
	void HideConsole();

	void GameUpdate();

	//This function is destined to be overriden by applications utilizing the engine
	virtual void Main();
	void do_MainLoop();

	Controller& get_Controller();
	GPU_Target& get_Renderer();

	const Uint64 get_Last();
	const double get_Delta();
	Vector2f& get_CameraMod();
	Vector2f& get_GlobalGravity();
	int& get_FPSLimit();

	Mask& get_Mask(int id);
	void add_Mask(std::vector<bool> flags, int priority);
	void delete_Mask(int id);

	void clear_Screen();

	void calculate_Delta();

	void refresh_FPS();
	void refresh_Event_SDL(); //who tf was responsible for mouse scroll?

	void print_FPS();

	void trash();

	Game();
	~Game();

protected:

	bool Quit = false;

	Uint64 Last = SDL_GetPerformanceCounter();
	int Timer = 0;

	double Delta = 0;

	int FPSLimit = 100;
	double FrameDelay = 0;

	Vector2f CameraMod = { 0.0f,0.0f };

	Vector2f GlobalGravity = { 0.0f, 1000.0f };

	std::map<int,std::unique_ptr<Mask>> Masks;

	Controller Controls;


	SDL_Event Event;

	GPU_Target* Renderer = nullptr;

	/*SDL_Window* Window = SDL_CreateWindow(
		"GAME",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WIDTH,
		HEIGHT,
		0
	);
	SDL_Renderer* GlobalRenderer = SDL_CreateRenderer(
		Window,
		-1,
		SDL_RENDERER_ACCELERATED
	);*/

};

/* First thing to initialize the engine system

* In order to initialize the program, you need to create class that derives from Game Base class
* All this new class needs is to override the Main() function to work properly

* After the creation, you just pass Heap-allocated object to this function and voila

 
This function will pass this object to ' Root ' smart pointer to be used by Nodes, Components, Data Bases etc.. 
* 
* */
void create_Game(Game* implementation);

#endif