#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>


#include "SphereCore.h"

#include "SObjects/DebugCursor.h"
#include "SObjects/Button.h"


//


std::string Message = "Agniś";


//

SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv)
{

   Root = new SphereCore; // init Engine Core;
   
   Root->init();

   //

   DebugCursor* cursor = Root->init_Member(new DebugCursor, nullptr, 1);

   Root->get_Mouse()->set_Cursor(cursor);

   GAR_Button* butt = Root->init_Member(new GAR_Button({ 300.0f, 300.0f }), nullptr, 1);



   //
   
   return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate)
{

    Root->listen_Loop();

    return SDL_APP_CONTINUE;

}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{

    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }

    // Keyboard
    if (event->type == SDL_EVENT_KEY_DOWN)
    {
        Root->get_Keyboard()->refresh(event);
    }
    //

    // Mouse
    Root->get_Mouse()->refresh(event);
    if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN)
    {
        Root->get_Mouse()->read_Input(event);
    }
    //

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    delete Root;
}