#include "BallEngine/Components/BasicComponents.h"
#include "BallEngine/EngineCore.h"
#include "BallEngine/DataStructures/DataStructures.h"

// MOVEMENT


void Speed_Component_Base::damp_Velocity()
{
	if (Velocity.x != 0)
	{
		Velocity.x = std::clamp(abs(Velocity.x) - Friction * (float)Root->get_Delta(), 0.0f, MaxSpeed.x) * sgn(Velocity.x);
	}

	if (Velocity.y != 0)
	{
		Velocity.y = std::clamp(abs(Velocity.y) - Friction * (float)Root->get_Delta(), 0.0f, MaxSpeed.y) * sgn(Velocity.y);
	}
}

void Speed_Component_Base::stop_Force() { Force = 0.0f; }

// 



// VISUAL
void Visual_Component_Base::relate_to_Camera(Node* user)
{
}

std::string Visual_Component_Base::get_TexturePath() { return TexturePath; }
void Visual_Component_Base::set_TexturePath(std::string path) { TexturePath = path; }
GPU_Image* Visual_Component_Base::get_Texture() { return Texture; }
void Visual_Component_Base::set_Texture(GPU_Image* val) { Texture = val; }

Vector2f Visual_Component_Base::get_Center()
{
	return{(float)(Texture->w/2), (float)(Texture->h/2)};
}

//



// VISUAL RECT

GPU_Rect& Visual_Component_Rect::get_Plane() { return Plane; }
void Visual_Component_Rect::set_Plane(Vector2f pos, Vector2f size)
{ 
	Plane = GPU_MakeRect(pos.x, pos.y, size.x, size.y);
}

void Visual_Component_Rect::relate_to_Camera(Node* user) 
{
	Plane.x = user->get_Position().x + Root->get_CameraMod().x + Offset.x;
	Plane.y = user->get_Position().y + Root->get_CameraMod().y + Offset.y;
}

Vector2f Visual_Component_Rect::get_Center()
{
	return{Plane.x + (float)(Texture->w) / 2, Plane.y + (float)(Texture->h) / 2 };
}


//



// VISUAL COMPONENT ARRAY

std::string Visual_Component_Array::get_TexturePath(int id) { return TexturePaths[id]; }
void Visual_Component_Array::add_TexturePath(std::string path) { TexturePaths.push_back(path); }
void Visual_Component_Array::delete_TexturePath(int id) { TexturePaths.erase(TexturePaths.begin() + id); }
GPU_Image* Visual_Component_Array::get_Texture(int id) { return Textures[id]; }
void Visual_Component_Array::add_Texture(GPU_Image* val) { Textures.push_back(val); }
void Visual_Component_Array::delete_Texture(int id) { Textures.erase(Textures.begin() + id); }

//



// TEXTBOX

std::string TextBox::get_FontPath() { return FontPath; }
void TextBox::set_FontPath(std::string val) { FontPath = val; }
TTF_Font* TextBox::get_Font() { return Font; }
void TextBox::set_Font(TTF_Font* val) { Font = val; }
int TextBox::get_FontSize() { return FontSize;}
void TextBox::set_FontSize(int val) { FontSize = val; }
SDL_Color TextBox::get_TextColor() { return TextColor; }
void TextBox::set_TextColor(SDL_Color val) { TextColor = val; }
std::string TextBox::get_Message() { return Message; }
void TextBox::set_Message(std::string val) { Message = val; }
GPU_Image* TextBox::get_Result() { return Result; }
GPU_Rect& TextBox::get_TextSurface() { return TextSurface; }
void TextBox::set_TextSurface(GPU_Rect val) { TextSurface = val; }

void TextBox::set_Position(Vector2f pos)
{
	TextSurface.x = pos.x;
	TextSurface.y = pos.y;
}

void TextBox::init() 
{
	int w, h;
	if (TTF_SizeUTF8(Font, Message.c_str(), &w, &h) == -1) { PRINT_ERROR "ERROR Calculating text width"; }
	TextSurface.w = w;
	TextSurface.h = h;
	
	Result = GPU_CopyImageFromSurface
	(
		TTF_RenderText_Blended_Wrapped
		(
			Font,
			Message.c_str(),
			TextColor,
			0
		)
	);
}

void TextBox::render(GPU_Rect* target = nullptr)
{
	if (target == nullptr) { target = &TextSurface; }
	GPU_BlitRect(Result, NULL, &Root->get_Renderer(), target);
}

TextBox::TextBox(std::string font_path, int font_size, std::string message, GPU_Rect rect) :
	FontPath(font_path),
	FontSize(font_size),
	Message(message),
	TextSurface(rect)
{
	Font = TTF_OpenFont(FontPath.c_str(), FontSize);
}

//



// COLLISION COMPONENT BASE

Colliding_Shape& Collision_Component_Base::pass_Shape() { std::cerr << "Used not overriden pass_Shape() function or Base Collision Component"; return *new Colliding_Shape(); }

//



// COLLISION CASTING MOLD

Collision_Component_Base& Collision_Component_Casting_Mold::get_Base() { return *Base; }
void Collision_Component_Casting_Mold::set_Base(Collision_Component_Base* base) { Base = base; }

Collision_Component_Casting_Mold::Collision_Component_Casting_Mold(Collision_Component_Base* base) { Base = base; }

//



//

CollisionPlane& Collision_Autonomic::get_CollisionMap() { return CollisionMap; }

Collision_Autonomic::Collision_Autonomic(std::pair<std::vector<int>,std::vector<int>> collision_planes) : CollisionMap(collision_planes){}
Collision_Autonomic::Collision_Autonomic(Collision_Component_Base* base, std::pair<std::vector<int>, std::vector<int>> collision_planes) :
	Collision_Component_Casting_Mold(base),
	CollisionMap(collision_planes) {}

//



// RECTANGLE

AABB& Rectangle_Component::get_Box() { return Box; }
Colliding_Shape& Rectangle_Component::pass_Shape() { return Box; }

Rectangle_Component::Rectangle_Component(Vector2f pos, Vector2f size, Node& owner) :
	Box(pos, size, owner) {}

Rectangle_Component::Rectangle_Component(Vector2f pos, Vector2f size, std::vector<int> col_layers, std::vector<int> col_masks, Mask& parent, Node& owner) :
	Box(pos, size, owner)
{
	Box.set_HashBelonging(parent.get_HashMap().where(&pass_Shape(), col_layers, col_masks));
}

void Rectangle_Component::destructor(Mask& parent)
{
	parent.get_HashMap().flush(&Box, Box.get_HashBelonging().first);
}

//



// COLLISION ARRAY BASE

Vector2f Collision_Array_Base::get_MinMaxX() { return MinMaxX; }
Vector2f Collision_Array_Base::get_MinMaxY() { return MinMaxY; }
void Collision_Array_Base::set_MinMaxX(Vector2f val) { MinMaxX = val; }
void Collision_Array_Base::set_MinMaxy(Vector2f val) { MinMaxY = val; }
void Collision_Array_Base::update_MinMaxX(float val) { MinMaxX.x = (val < MinMaxX.x) ? val : MinMaxX.x; MinMaxX.y = (val > MinMaxX.y) ? val : MinMaxX.y; }
void Collision_Array_Base::update_MinMaxY(float val) { MinMaxY.x = (val < MinMaxY.x) ? val : MinMaxY.x; MinMaxY.y = (val > MinMaxY.y) ? val : MinMaxY.y; }
void Collision_Array_Base::update_MinMaxX(float min, float max) { MinMaxX.x = (min < MinMaxX.x) ? min : MinMaxX.x; MinMaxX.y = (max > MinMaxX.y) ? min : MinMaxX.y; }
void Collision_Array_Base::update_MinMaxY(float min, float max) { MinMaxY.x = (min < MinMaxY.x) ? min : MinMaxY.x; MinMaxY.y = (max > MinMaxY.y) ? max : MinMaxY.y; }

Vector2f Collision_Array_Base::get_Center() { return {std::lerp(MinMaxX.x, MinMaxX.y, 0.5f), std::lerp(MinMaxX.x, MinMaxX.y, 0.5f) }; }

//

//