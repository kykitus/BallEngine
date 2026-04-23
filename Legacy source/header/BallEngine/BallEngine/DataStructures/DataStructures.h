#ifndef PACMAN_DATA_STRUCTURES
#define PACMAN_DATA_STRUCTURES

#include "BallEngine/Types.h"

// SPATIAL HASH MAP

class Spatial_Hash_Map
{
public:

	bool check_HashMapCell(float key);
	std::vector<Colliding_Shape*> get_HashMapCell(float key);
	size_t get_HashMapSize();

	int get_Cell(float val);

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

#endif