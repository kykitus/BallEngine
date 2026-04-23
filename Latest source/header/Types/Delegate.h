#ifndef BE_DELEGATE
#define BE_DELEGATE

#include <vector>
#include <string>
#include <iostream>
#include <functional>

#include "GObject.h"

class Alarm 
{
public:

	void emit() { for (auto [key, recipent] : Listeners) { for (auto f : recipent) { f(); } } };
	
	void add_Listener(std::function<void()> listener, GObject* obj) { Listeners[obj]; Listeners[obj].push_back(listener); };
	void clear_Listener(GObject* obj)
	{
		if (Listeners.count(obj)) { Listeners.erase(obj); }
		else { throw std::invalid_argument("no listening object like this exists here"); }
	};

	std::unordered_map<GObject*, std::vector<std::function<void()>>>& get_List() { return Listeners; };


private:

	std::unordered_map<GObject*, std::vector<std::function<void()>>> Listeners;

};


template <typename ... Args>
class AlarmWA
{
public:

	void emit(Args&&... args) { for (auto [key, recipent] : Listeners) { for (auto f : recipent) { f(args...); } } };


	void add_Listener(std::function<void(Args...)> listener, GObject* obj) { Listeners[obj]; Listeners[obj].push_back(listener); };
	void clear_Listener(GObject* obj)
	{
		if (Listeners.count(obj)) { Listeners.erase(obj); }
		else { throw std::invalid_argument("no listening object like this exists here"); }
	};

	std::unordered_map<GObject*, std::vector<std::function<void(Args...)>>>& get_List() { return Listeners; };


private:
	
	std::unordered_map<GObject*, std::vector<std::function<void(Args...)>>> Listeners;

};

#endif
