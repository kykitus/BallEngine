#ifndef BE_LOGGER
#define BE_LOGGER

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <string>

#include "Types/Vectors.h"


enum Logger_Flags
{
	LO_FLUSH_EVERY_TICK,
	LO_QUEUE_LOGS,
	LO_INCREMENT_SIZE_WHEN_NOT_ENOUGH_SPACE,
	LO_DECREMENT_SIZE_WHEN_ENOUGH_SPACE,
	LO_HIDE
};

class ENGN_Logger 
{
public:
	void init();

	void push_Log(std::string log);
	void flush();

	void paste();

	void switch_Visibility();

	ENGN_Logger();

	std::string& get_Text();
	void set_Text(std::string text);
	Vector2f& get_Position();
	void set_Position(Vector2f pos);
	Vector2f& get_Size();
	void set_Size(Vector2f pos);
	uint8_t& get_Flags();
	void set_Flags(uint8_t val);


private:

	std::string Text;
	TTF_Font* Font;

	Vector2f Position = {5.0f, 5.0f};
	Vector2f Size = {170.0f, 220.0f};

	SDL_FRect Rect;

	uint8_t Flags =
		(1 << LO_FLUSH_EVERY_TICK) |
		(1 << LO_INCREMENT_SIZE_WHEN_NOT_ENOUGH_SPACE) |
		(1 << LO_DECREMENT_SIZE_WHEN_ENOUGH_SPACE);
		//(1 << LO_HIDE);

};

#endif
