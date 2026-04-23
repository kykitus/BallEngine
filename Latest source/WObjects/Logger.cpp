#include "WObjects/Logger.h"



#include "SphereCore.h"


void ENGN_Logger::init()
{
    // Inputs

    Root->get_Keyboard()->add_KeyListener(SDLK_L, std::bind(&ENGN_Logger::switch_Visibility, this), nullptr);

    //
}

void ENGN_Logger::push_Log(std::string log) { Text += log + "\n"; }
void ENGN_Logger::flush() { Text = ""; }

void ENGN_Logger::paste()
{

    if (Text != "" && !check_Flag(Flags, LO_HIDE))
    {
        SDL_Renderer* renderer = Root->get_Renderer();

        SDL_Color color = { 255, 255, 255, 255 };

        SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(Font, Text.c_str(), 0, color, Size.x - 5);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FRect rect = { Position.x + 5, Position.y + 5, surface->w, surface->h };

        SDL_SetRenderDrawColor(renderer, 107, 91, 99, 100);
        SDL_RenderFillRect(renderer, &Rect);

        SDL_RenderTexture(renderer, texture, nullptr, &rect);

        SDL_DestroySurface(surface);
        SDL_DestroyTexture(texture);
    }
}

void ENGN_Logger::switch_Visibility() { Flags ^= (1 << LO_HIDE); }

ENGN_Logger::ENGN_Logger()
{
    Font = TTF_OpenFont("Resources/Fonts/Logger_Regular.ttf", 16);

    if (!Font) {
        throw std::invalid_argument("Font not loaded successfuly");
    }

    Rect = { Position.x, Position.y, Size.x, Size.y };

}





std::string& ENGN_Logger::get_Text() { return Text; }
void ENGN_Logger::set_Text(std::string text) { Text = text; }
Vector2f& ENGN_Logger::get_Position(){ return Position; }
void ENGN_Logger::set_Position(Vector2f pos) { Position = pos; }
Vector2f& ENGN_Logger::get_Size() { return Size; }
void ENGN_Logger::set_Size(Vector2f pos) { Size = pos; }
uint8_t& ENGN_Logger::get_Flags(){ return Flags; }
void ENGN_Logger::set_Flags(uint8_t val) { val = Flags; }
