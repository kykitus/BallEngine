#ifndef PACMAN_DATA_STRUCTURES
#define PACMAN_DATA_STRUCTURES

#include "BallEngine/Types.h"
#include "BallEngine/Nodes/Nodes.h"

// SPATIAL HASH MAP

class Spatial_Hash_Map
{
public:

	bool check_HashMapCell(float key);
	std::vector<Colliding_Shape*> get_HashMapCell(float key);
	size_t get_HashMapSize();

	int get_Cell(float val);

	int cantor_hash(int x, int y);

	const int set_Hash(float x, float y, int col_layer);
	void insert(int xi, int yi, int col_layer, Colliding_Shape* col);

	std::pair<std::vector<int>, std::vector<int>> where(Colliding_Shape* obj, std::vector<int> colliosion_layers, std::vector<int> collision_masks);
	void flush(Colliding_Shape* obj, const std::vector<int> belonging);

	Spatial_Hash_Map() = default;
	Spatial_Hash_Map(float spacing_val, Vector2i length_val);

	~Spatial_Hash_Map();

private:

	float Spacing = 100;
	Vector2i Length = { 100, 100 };

	std::unordered_map<float, std::vector<Colliding_Shape*>> HashIndex;
};

//



// TEXTURE REPOSITORY

class Texture_Repository
{
public:

	GPU_Image* request(std::string path);
	void delete_Texture(std::string path);
	void flush();

	size_t size();

	Texture_Repository() = default;

	~Texture_Repository();
private:

	std::unordered_map<std::string, GPU_Image*> Repository;

};

//



// SYSTEM MACRO PANEL

class SystemMacroPanel 
{
public:

	Vector2i get_ScreenSize();
	void set_Screensize(Vector2i val);
	std::string get_EnginePath();
	void set_EnginePath(std::string val);

	Vector2f get_RectSize();
	void set_RectSize(Vector2f val);

	float get_MinShapeDistance();
	void set_MinShapeDistance(float val);
	Vector2f get_MaxSpeed();
	void set_MaxSpeed(Vector2f val);

private:

	// App

	Vector2i ScreenSize = {1280, 720};
	std::string EnginePath = "header/BallEngine";

	// Shapes

	Vector2f RectSize = { 80.0f, 80.0f };

	// Physics

	float MinShapeDistance = 0.01f;

	Vector2f MaxSpeed = { 150.0f, 150.0f };

};

//



#endif