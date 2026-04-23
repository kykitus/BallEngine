#include "Types/Assets/Image.h"

#include "SphereCore.h"


void Image::print()
{
	SDL_RenderTexture(Root->get_Renderer(), Texture, nullptr, &Body);
}

void Image::load(std::string path)
{
	SDL_Surface* surface = IMG_Load(path.c_str());
	Texture = SDL_CreateTextureFromSurface(Root->get_Renderer(), surface);
	SDL_DestroySurface(surface);
}

Image::Image()
{
}

Image::~Image()
{
	SDL_DestroyTexture(Texture);
}


void Image::set_Position(Vector2f pos) { Body.x = pos.x; Body.y = pos.y; }
void Image::add_Position(Vector2f pos) { Body.x += pos.x; Body.y += pos.y; }
Vector2f Image::get_Position() { return { Body.x, Body.y }; }

void Image::set_Texture(SDL_Texture* tex) { Texture = tex; }
SDL_Texture* Image::get_Texture() { return Texture; }

void Image::set_Body(Vector2f pos, Vector2f size)
{
	Body.x = pos.x;
	Body.y = pos.y;
	Body.w = size.x;
	Body.h = size.y;
}
void Image::set_Body(SDL_FRect& rect) { Body = rect; }
SDL_FRect Image::get_Body(){ return Body; }

void Image::set_Tile(Vector2f pos, Vector2f size)
{
	Tile.x = pos.x;
	Tile.y = pos.y;
	Tile.w = size.x;
	Tile.h = size.y;
}
void Image::set_Tile(SDL_FRect& rect) { Tile = rect; }
SDL_FRect Image::get_Tile() { return Tile; }

void Image::set_Modulation(SDL_FColor color) 
{
	Modulation = color;
	SDL_SetTextureColorModFloat(Texture, color.r, color.g, color.b);
	SDL_SetTextureAlphaModFloat(Texture, color.a);
}

SDL_FColor& Image::get_Modulation() { return Modulation; }


