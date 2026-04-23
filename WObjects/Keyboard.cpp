#include "WObjects/Keyboard.h"

#include "GObject.h"

//#include "iostream"

void ENGN_Keyboard::refresh(SDL_Event* event)
{
	for (auto [key, functionality] : ListeningKeys) 
	{
		if (event->key.key == key) { functionality.emit(); }
	}
}

void ENGN_Keyboard::add_KeyListener(int key, const std::function<void()> func, GObject* obj)
{
	if (!ListeningKeys.count(key)) { ListeningKeys[key]; }
	ListeningKeys[key].add_Listener(func, obj);
}

Alarm& ENGN_Keyboard::get_Key(int key)
{
	return ListeningKeys[key];
}

void ENGN_Keyboard::refresh_KeyListeners()
{
	for (auto it = ListeningKeys.begin(); it != ListeningKeys.end();)
	{ 
		if (!it->second.get_List().size()) { it = ListeningKeys.erase(it); }
		else { it++; }
	}
}
