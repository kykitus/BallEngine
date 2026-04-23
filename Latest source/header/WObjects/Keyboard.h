#ifndef BE_KEYBOARD
#define BE_KEYBOARD

#include "SDL3/SDL.h"

#include <unordered_map>

#include "Types/Delegate.h"

class ENGN_Keyboard 
{
public:

	virtual void refresh(SDL_Event* event);

	// key is designated by SDL_SCANCODE_...
	// func is pointer to func
	//
	// remove_KeyListener works with same parameters
	void add_KeyListener(int key, const std::function<void()> func, GObject* obj);
	Alarm& get_Key(int key);
	void refresh_KeyListeners();

protected:

	std::unordered_map<int, Alarm> ListeningKeys;

};

#endif
