#ifndef BE_COG
#define BE_COG

#include <functional>
#include <map>
#include <memory>

#include "GObject.h"


class Cog : public GObject 
{
public:

	// First Frame Task
	virtual void Ready();
	// Update Per Frame
	virtual void Tick();
	// Render Per Frame
	virtual void Render();
	// Physics Tick every 1/60 second
	virtual void Physics();

	Cog& get_Child(int index);
	void add_Child(std::shared_ptr<Cog> child);
	void remove_Child(int index);
	std::vector<std::shared_ptr<Cog>>& get_Children();

	void poke(int val, Cog& caller);
	void use(std::function<void(Cog& caller)>);

	bool get_IsTicking();
	void set_IsTicking(bool is);
	bool get_IsPhysicing();
	void set_IsPhysicing(bool is);


	const static uint8_t Rectivity = 1;

protected:

	std::map<int, std::function<void(Cog& caller)>> Interaction; // List of reaction funcs for specific pokes

	std::vector<std::shared_ptr<Cog>> Children;


	bool IsTicking = true;
	bool IsPhysicing = true;

};


#endif
