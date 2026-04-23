#ifndef BE_IMAGE
#define BE_IMAGE

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "Types/Vectors.h"
#include "Types/Asset.h"

class Image : public Asset
{
public:

	virtual void print();

	virtual void load(std::string path);



	Image();
	~Image();

	void set_Position(Vector2f pos);
	void add_Position(Vector2f pos);
	Vector2f get_Position();

	void set_Texture(SDL_Texture* tex);
	SDL_Texture* get_Texture();
	void set_Body(Vector2f pos, Vector2f size);
	void set_Body(SDL_FRect& rect);
	SDL_FRect get_Body();
	void set_Tile(Vector2f pos, Vector2f size);
	void set_Tile(SDL_FRect& rect);
	SDL_FRect get_Tile();
	void set_Modulation(SDL_FColor color);
	SDL_FColor& get_Modulation();

protected:

	SDL_Texture* Texture;
	SDL_FRect Body;
	SDL_FRect Tile;
	SDL_FColor Modulation;

};

#endif
