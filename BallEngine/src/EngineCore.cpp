#include "BallEngine/EngineCore.h"




bool Mask::get_Sleep() { return IsAsleep; }
void Mask::set_Sleep(bool val) { IsAsleep = val; }
bool Mask::get_Visible() { return IsVisible; }
void Mask::set_Visible(bool val) { IsVisible = val; }
bool Mask::get_HaveControls() { return HaveControls; }
void Mask::set_HaveControls(bool val) { HaveControls = val; }
bool Mask::get_HaveHash() { return HaveHash; }
void Mask::set_HaveHash(bool val) { HaveHash = val; }
bool Mask::get_HaveTextureRep() { return HaveTextureRep; }
void Mask::set_HaveTextureRep(bool val) { HaveTextureRep = val; }
bool Mask::get_HaveActionReg() { return HaveActionReg; }
void Mask::set_HaveActionReg(bool val) { HaveActionReg = val; }

std::map<int, std::vector<std::shared_ptr<Node>>>& Mask::get_Nodes() { return UpdateList; }

Input& Mask::get_Input() { return *Controls; }
Spatial_Hash_Map& Mask::get_HashMap() { return *HashMap; }
Texture_Repository& Mask::get_TextureRep() { return *TextureRep; }
Control_Journal& Mask::get_ActionReg() { return *ActionRegistry; }


void Mask::control_call(int num) 
{
	Controls->use_Key(num, nullptr);
}


void Mask::do_Sequence() 
{
	for (std::function<void()> task : Sequence) { task(); }
}

void Mask::update()
{
	for (auto& [key, value] : UpdateList) 
	{
		for (auto& obj : value)
		{
			obj->process_delta();
		}
	}
}

void Mask::render() 
{
	for (auto& [key, value] : RenderList)
	{
		for (auto& obj : value)
		{
			obj->render();
		}
	}
}

void Mask::clear_Lists() 
{
	UpdateList.clear();
	RenderList.clear();
}

Mask::Mask(std::vector<bool> flags) : Controls()
{
	if (flags[S_SLEEP]) { IsAsleep = true; }
	if (flags[S_VISIBLE]) { IsVisible = true; }

	if (flags[REQ_CONTROLS]) 
	{
		Controls = std::make_unique<Input>(); HaveControls = true;
	}
	if (flags[REQ_UPDATE]) 
	{ 
		ActionRegistry = std::make_unique<Control_Journal>(); HaveActionReg = true;
		Sequence.push_back(std::bind(&Control_Journal::update, &*ActionRegistry));

		Sequence.push_back(std::bind(&Mask::update, this));
		if (flags[REQ_HASH_MAP]) { HashMap = std::make_unique<Spatial_Hash_Map>(); HaveHash = true; }
	}
	if (flags[REQ_RENDER])
	{
		Sequence.push_back(std::bind(&Mask::render, this));
		if (flags[REQ_TEXTURE_REP]) { TextureRep = std::make_unique<Texture_Repository>(); HaveTextureRep = true;}
	}
	
}

//



//

Mask& Controller::get_Focus() { return *Focus; }
void Controller::set_Focus(Mask& val) { if (val.get_HaveControls()) { Focus = &val; } else { throw std::runtime_error("Error 2201: Input: Target Simulation does not have Controls"); } }

Keyboard& Controller::get_Keyboard() { return Keys; }
Mouse& Controller::get_Mouse() { return Points; }

void Controller::refresh() 
{
	Root->refresh_Event_SDL();
	Keys.refresh(&*Focus);
	Points.refresh_Mouse();
	Points.refresh_Cursor();
}

//



//

void Game::Init()
{
	//if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { std::cerr << "error initializing SDL: %s\n" << SDL_GetError(); } Already Used by SDL_GPU
	if (Renderer == NULL) { std::cerr << "Renderer is NULL"; }
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) { std::cerr << "Error initialising SDL_Image"; };
	if (TTF_Init() == -1) { PRINT_ERROR "TTF not initialized"; }
	HideConsole();

	SDL_ShowCursor(SDL_DISABLE);
}

void Game::HideConsole()
{
	ShowWindow(GetConsoleWindow(), SW_SHOW);
}

void Game::GameUpdate()
{
	for (auto& [key, value] : Masks) {
		value->do_Sequence();
	}

}

Controller& Game::get_Controller() { return Controls; }

GPU_Target& Game::get_Renderer() { return *Renderer; }

Mask& Game::get_Mask(int id) { return *Masks[id]; }

const Uint64 Game::get_Last() { return Last; }
const double Game::get_Delta() { return Delta; }
Vector2f& Game::get_CameraMod() { return CameraMod; }
Vector2f& Game::get_GlobalGravity() { return GlobalGravity; }
int& Game::get_FPSLimit() { return FPSLimit; }

void Game::add_Mask(std::vector<bool> flags, int priority) { Masks[priority] = std::make_unique<Mask>(flags); }
void Game::delete_Mask(int priority) { Masks.erase(priority); }

void Game::clear_Screen() 
{
	GPU_ClearRGBA(Renderer, 122, 211, 211, 255);
}

void Game::calculate_Delta() 
{
	Delta = (SDL_GetPerformanceCounter() - Last) / static_cast<double>(SDL_GetPerformanceFrequency());

	if (Delta < FrameDelay)
	{
		SDL_Delay(FrameDelay - Delta);

		Delta = (SDL_GetPerformanceCounter() - Last) / static_cast<double>(SDL_GetPerformanceFrequency());
	}
	Last = SDL_GetPerformanceCounter();

	Delta = Delta;
}

void Game::refresh_FPS()
{
	FrameDelay = 1000 / FPSLimit;
}

void Game::refresh_Event_SDL() 
{
	Controls.get_Mouse().set_WheelDirection(0);
	while (SDL_PollEvent(&Event)) {
		switch (Event.type) {
		case SDL_QUIT:
			Quit = true;
			break;
		case SDL_WINDOWEVENT:
			if (Event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED) { break; }
			break;
		case SDL_MOUSEWHEEL:
			Controls.get_Mouse().set_WheelDirection(sgn(Event.wheel.y));
			Controls.get_Mouse().add_ActionQueue(-1 + (-1 * (-1 == Controls.get_Mouse().get_WheelDirection())));
			break;
		}
	}
}

void Game::print_FPS() 
{
	PRINT "\nfps: " << 1.0 / Delta << "\n";
	PRINT "delta: " << Delta << "\n\n";
	PRINT "\nfpsdealy: " << FPSLimit << "\n";
}

void Game::trash() 
{
	for (auto& [key, mask] : Masks)
	{
		mask->clear_Lists();
	}
}

Game::Game() 
{
	Renderer = GPU_Init
	(
		MacroPanel.get_ScreenSize().x,
		MacroPanel.get_ScreenSize().y,
		GPU_DEFAULT_INIT_FLAGS
	);
}

Game::~Game()
{
	GPU_FreeTarget(Renderer);
	SDL_Quit();
	TTF_Quit();
	GPU_Quit();
}

void create_Game(Game* implementation) { Root = std::unique_ptr<Game>(implementation); }

