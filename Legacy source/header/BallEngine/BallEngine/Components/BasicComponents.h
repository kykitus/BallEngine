#ifndef SDL_ENGINE_BCOMP
#define SDL_ENGINE_BCOMP

#include "BallEngine/Types.h"
#include "BallEngine/Elements/Elements.h"
#include "BallEngine/Elements/CollisionPhysics.h"

// MOVEMENT

class Speed_Component_Base 
{
public:

	Vector2f Velocity = { 0.0f, 0.0f };
	Vector2f MaxSpeed = { 400, 400 };
	Vector2f Direction = { 1.0f, 1.0f };

	Vector2f Force = { 0.0f, 0.0f };
	float Mass = 1;
	float Friction = 400;

	virtual void damp_Velocity();
	virtual void stop_Force();
};

//



// VISUAL

class Visual_Component_Base
{
public:

	virtual void relate_to_Camera(Node* user);

	virtual std::string get_TexturePath();
	void set_TexturePath(std::string path);
	GPU_Image* get_Texture();
	void set_Texture(GPU_Image* val);
	virtual Vector2f get_Center();

protected:
	Vector2f Offset = { 0.0f , 0.0f };
	std::string TexturePath;
	GPU_Image* Texture = NULL;

};

class Visual_Component_Rect : public Visual_Component_Base
{
public:

	GPU_Rect& get_Plane();
	void set_Plane(Vector2f pos, Vector2f size);

	virtual void relate_to_Camera(Node* user);
	virtual Vector2f get_Center();

protected:

	GPU_Rect Plane;

};

class Visual_Component_Array 
{
public:

	std::string get_TexturePath(int id);
	void add_TexturePath(std::string path);
	void delete_TexturePath(int id);
	GPU_Image* get_Texture(int id);
	void add_Texture(GPU_Image* val);
	void delete_Texture(int id);



protected:

	std::vector<std::string> TexturePaths;
	std::vector<GPU_Image*> Textures;

	std::vector<std::tuple<bool, int, GPU_Rect>> Planes;

};

class TextBox 
{
public:

	std::string get_FontPath();
	void set_FontPath(std::string val);
	TTF_Font* get_Font();
	void set_Font(TTF_Font* val);
	int get_FontSize();
	void set_FontSize(int val);
	SDL_Color get_TextColor();
	void set_TextColor(SDL_Color val);
	std::string get_Message();
	void set_Message(std::string val);
	GPU_Image* get_Result();
	GPU_Rect& get_TextSurface();
	void set_TextSurface(GPU_Rect val);

	void set_Position(Vector2f pos);

	void init();

	void render(GPU_Rect* target);

	TextBox(std::string font_path, int font_size, std::string message, GPU_Rect rect);

private:

	std::string FontPath;
	TTF_Font* Font;
	int FontSize = 10;
	SDL_Color TextColor = { 0, 0, 0 };
	GPU_Rect TextSurface;
	std::string Message;

	GPU_Image* Result;

};

//



// COLLISION BODY

class Collision_Component_Base
{
public:

	virtual Colliding_Shape& pass_Shape();

	Collision_Component_Base() = default;

};

//



//

class Collision_Component_Casting_Mold : public Collision_Component_Base
{
public:

	Collision_Component_Base& get_Base();
	void set_Base(Collision_Component_Base* base);

	Collision_Component_Casting_Mold() = default;
	Collision_Component_Casting_Mold(Collision_Component_Base* base);

protected:

	Collision_Component_Base* Base;

};

//



//


class Collision_Autonomic : public Collision_Component_Casting_Mold //Decorator Pattern Here :D
{
public:

	CollisionPlane& get_CollisionMap();

	using Collision_Component_Casting_Mold::Collision_Component_Casting_Mold;
	Collision_Autonomic(std::pair<std::vector<int>, std::vector<int>> collision_planes);
	Collision_Autonomic(Collision_Component_Base* base, std::pair<std::vector<int>, std::vector<int>> collision_planes);

protected:

	CollisionPlane CollisionMap;

};

//



//

class Rectangle_Component : public Collision_Component_Base
{
public:
	AABB& get_Box();
	Colliding_Shape& pass_Shape();

	Rectangle_Component() = default;
	Rectangle_Component(Vector2f pos, Vector2f size, Node& owner);
	Rectangle_Component(Vector2f pos, Vector2f size, std::vector<int> col_layers, std::vector<int> col_masks, Mask& parent, Node& owner);

	void destructor(Mask& parent);

protected:

	AABB Box;

};

//



//

class Collision_Array_Base : public Collision_Component_Base
{
public:

	Vector2f get_MinMaxX();
	Vector2f get_MinMaxY();
	void set_MinMaxX(Vector2f val);
	void set_MinMaxy(Vector2f val);
	void update_MinMaxX(float val);
	void update_MinMaxY(float val);
	void update_MinMaxX(float min, float max);
	void update_MinMaxY(float min, float max);
	Vector2f get_Center();

protected:

	Vector2f MinMaxX = { 0.0f, 0.0f };
	Vector2f MinMaxY = { 0.0f, 0.0f };

};

//

#endif
