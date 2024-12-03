#include "BallEngine/EngineCore.h"
#include "BallEngine/AllObjects.h"

class Test : public Effigy
{
public:

	void render() override 
	{
		first.render(&first.get_TextSurface());
	}

	TextBox first;

	Test() :
		first
		(
			"Resources/wierd.ttf",
			20,			
			"Pierd",
			GPU_MakeRect(100,100,240,70)
		)
	{
		first.init();
	}

};


void Game::Main()
{
	Init();

	refresh_FPS();

	Root->add_Mask({ 0,0,1,1,1,1,1 }, 2);

	Root->get_Controller().set_Focus(Root->get_Mask(2));

	Test* test = Root->get_Mask(2).init_Member
	(
		new Test(),
		1, 1, false, true
	);

	DebugActor* First = Root->get_Mask(2).init_Member(
		new DebugActor(2),
		1, 1, true, true);

	/*First->set_Position({ 500, 500 });
	First->refresh_Position();

	First->set_Position({ 900, 900 });

	DebugCursor* TestOne = Root->get_Mask(2).init_Member(
		new DebugCursor(2, { 200, 300 }, { 20, 20 }),
		1, 1, true, true);

	Controls.get_Mouse().set_Cursor(TestOne);

	Actor* Second = Root->get_Mask(2).init_Member(
		new Actor(2, { 200.0f, 200.0f }, { 300.0f,300.0f }),
		1, 1, true, true);*/

	Root->get_Mask(2).get_Input().replace_Key(&*First->Control[0], 0);
	Root->get_Mask(2).get_Input().replace_Key(&*First->Control[1], 1);
	Root->get_Mask(2).get_Input().replace_Key(&*First->Control[2], 2);
	Root->get_Mask(2).get_Input().replace_Key(&*First->Control[3], 3);
	Root->get_Mask(2).get_Input().replace_Key(&*First->Control[4], 4);
	Root->get_Mask(2).get_Input().replace_Key(&*First->Control[5], 5);


	/*Tile_Map* essa = Root->get_Mask(2).init_Member(
		new Tile_Map(2, "Data/DemoClassSet.txt", "Data/pacman.txt", "Textures/sciany.png"),
		1, 1, true, true);*/


	while (!Quit)
	{
		do_MainLoop();
	}
	trash();
}

void Game::do_MainLoop()
{
	// CONTROL

	Controls.refresh();

	//



	// CLEAR

	clear_Screen();

	//



	// UPDATE

	GameUpdate();

	//



	// DELTA TIME

	calculate_Delta();

	//



	// DEBUG CHECK

	print_FPS();

	//



	// SCREEN

	GPU_Flip(Renderer);

	//
}