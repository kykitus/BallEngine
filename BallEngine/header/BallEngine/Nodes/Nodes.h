#ifndef PACMAN_NODES
#define PACMAN_NODES

#include "BallEngine/Types.h"

// NODE

class Node
{
public:

	void poke(int val, Node& caller);
	void use(std::function<void(Node& caller)>);

	bool get_Sleep();
	void set_Sleep(bool val);
	Mask& get_Mask();

	Vector2f get_Position();
	virtual void set_Position(Vector2f val);

	virtual void process_delta();
	virtual void render();

	Node() = default;
	Node(uint8_t parent);

	virtual ~Node();

protected:

	Vector2f Position = { 23.0f, 23.0f }; //logic position in the center of the body

	std::unordered_map<int, std::function<void(Node& caller)>> Interaction; // List of reaction funcs for specific pokes
	bool IsStatic = false;
	bool IsMovable = false; // only when static is false
	bool IsAsleep = false;
	uint8_t ParentMask;

};

//



//

class Effigy : virtual public Node
{
public:

	bool get_IsVisible();
	void set_IsVisible(bool val);

	virtual void render();

	Effigy() = default;
	virtual ~Effigy() = default;

private:


	bool IsVisible = true;
};

#endif
