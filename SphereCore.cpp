#include "SphereCore.h"

#include <iostream>

#include "Flags.h"


void SphereCore::init()
{
    Mouse->init();
    Logger->init();
}

void SphereCore::start_Newbies()
{
    for (Cog* newbie : ReadyList) 
    {
        newbie->Ready();
    }
    ReadyList.clear();

}

void SphereCore::Cog_Tick(Cog* obj) 
{
    obj->Tick();
    for (auto child : obj->get_Children())
    {
        Cog_Tick(&*child); 
    }
}

void SphereCore::listen_PhysicsTimer()
{
    if ((SDL_GetPerformanceCounter()) / static_cast<double>(SDL_GetPerformanceFrequency()) > PhysicsDelay)
    {
        Cog_PhysicsTick(DrivingCog.get());
    }
    PhysicsDelay += 60000;
}

void SphereCore::Cog_PhysicsTick(Cog* obj)
{
    obj->Physics();
    for (auto child : obj->get_Children())
    {
        Cog_PhysicsTick(&*child);
    }
}

void SphereCore::Render()
{
    for (auto [key, layer] : RenderList)
    {
        for (auto obj : layer)
        {
            obj->Render();
        }
    }
}


void SphereCore::Loop()
{
    clear_Screen();


    start_Newbies();


    Cog_Tick(&*DrivingCog);


    listen_PhysicsTimer();

    // Free Space

    Logger->paste();

    //


    SDL_RenderPresent(Renderer);


    // Free Space

    Logger->flush();

    //
}

void SphereCore::clear_Screen()
{
    SDL_SetRenderDrawColor(Renderer, 102, 68, 88, 255);
    SDL_RenderClear(Renderer);
}

void SphereCore::calculate_Delta()
{
    Delta = (SDL_GetPerformanceCounter() - Last) / static_cast<double>(SDL_GetPerformanceFrequency());

    if (Delta < FrameDelay)
    {
        SDL_Delay((FrameDelay - Delta) * 1000);

        Delta = (SDL_GetPerformanceCounter() - Last) / static_cast<double>(SDL_GetPerformanceFrequency());
    }
    Last = SDL_GetPerformanceCounter();


}

void SphereCore::listen_Loop()
{
    Delta = (SDL_GetPerformanceCounter() - Last) / static_cast<double>(SDL_GetPerformanceFrequency());
    FrameDelayCounter += Delta;

    while (FrameDelayCounter >= FrameDelay)
    {
        Loop();

        Logger->push_Log("Delta: " + std::to_string(Delta));
        Logger->push_Log("FPS: " + std::to_string(1.0 / Delta));

        FrameDelayCounter -= FrameDelay;
        FrameCounter++;
    }
    Last = SDL_GetPerformanceCounter();


}

void SphereCore::refresh_FPS()
{
    FrameDelay = 1.0 / FPSLimit;
}



SphereCore::SphereCore()
{
    TTF_Init();

    WindowSize = { 1920, 1080 };

    if (!SDL_CreateWindowAndRenderer("Hello World", WindowSize.x, WindowSize.y, SDL_WINDOW_FULLSCREEN, &Window, &Renderer)) {
        throw std::invalid_argument("failed to load Window and Renderer" + std::string(SDL_GetError()));
    }

    SDL_SetRenderScale(Renderer, RenderScale.x, RenderScale.y);
    SDL_SetRenderDrawBlendMode(Renderer, SDL_BLENDMODE_BLEND);
    SDL_GetRenderOutputSize(Renderer, &DrawableSize.x, &DrawableSize.y);
    SDL_SetRenderVSync(Renderer, 1);

    refresh_FPS();

    //SDL_SetRenderTextWrap(Renderer, SDL_TRUE);

    DrivingCog = std::shared_ptr<Cog>(new Cog());

    Keyboard = new ENGN_Keyboard();
    Mouse = new ENGN_Mouse();
    Logger = new ENGN_Logger();
    CollisionMap = new SpatialHashMap();

}

SphereCore::~SphereCore()
{
    delete Keyboard;
    delete Mouse;
    delete Logger;
    delete CollisionMap;
}

Cog& SphereCore::get_DrivingCog() { return *DrivingCog.get(); }

ENGN_Keyboard* SphereCore::get_Keyboard() { return Keyboard; }
ENGN_Mouse* SphereCore::get_Mouse() { return Mouse; }
ENGN_Logger* SphereCore::get_Logger() { return Logger; }
SpatialHashMap* SphereCore::get_CollisionMap() { return CollisionMap; }


SDL_Window* SphereCore::get_Window() { return Window; }
SDL_Renderer* SphereCore::get_Renderer() { return Renderer; }

Vector2i& SphereCore::get_WindowSize() { return WindowSize; }
void SphereCore::set_WindowSize(Vector2i size) { WindowSize = size; }
Vector2f& SphereCore::get_RenderScale() { return RenderScale; }
void SphereCore::set_RenderScale(Vector2f scale) { RenderScale = scale; }

const Uint64 SphereCore::get_Last() { return Last; }
const double SphereCore::get_Delta() { return Delta; }
Vector2f& SphereCore::get_CameraMod() { return CameraMod; }
int& SphereCore::get_FPSLimit() { return FPSLimit; }

SphereCore* Root = nullptr;