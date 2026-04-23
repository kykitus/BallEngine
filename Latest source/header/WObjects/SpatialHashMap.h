#ifndef BE_SPATIALHASHMAP
#define BE_SPATIALHASHMAP

#include <vector>

#include "Types/Collision.h"
#include "Types/Numbers.h"

class SpatialHashMap
{
public:

	bool check_HashMapCell(float key);
	std::vector<CollidingShape*> get_HashMapCell(float key);
	size_t get_HashMapSize();

	int get_Cell(float val);

	const int set_Hash(float x, float y, int col_layer);
	void insert(int xi, int yi, int col_layer, CollidingShape* col);

	std::pair<std::vector<int>, std::vector<int>> where(CollidingShape* obj, std::vector<int> colliosion_layers, std::vector<int> collision_masks);
	void flush(CollidingShape* obj, const std::vector<int> belonging);

	uint64_t rent_UID();

	SpatialHashMap() = default;
	SpatialHashMap(float spacing_val, Vector2i length_val);

	~SpatialHashMap();

private:

	float Spacing = 100;
	Vector2i Length = { 100, 100 };

	uint64_t IDCounter = 0;

	std::unordered_map<float, std::vector<CollidingShape*>> HashIndex;
};

#endif