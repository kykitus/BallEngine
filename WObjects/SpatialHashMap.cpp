#include "WObjects/SpatialHashMap.h"

bool SpatialHashMap::check_HashMapCell(float key) { return HashIndex.count(key); }

std::vector<CollidingShape*> SpatialHashMap::get_HashMapCell(float key) { return HashIndex[key]; }

size_t SpatialHashMap::get_HashMapSize()
{
	return HashIndex.size();
}

int SpatialHashMap::get_Cell(float val) { return floor(val / Spacing); }

const int SpatialHashMap::set_Hash(float x, float y, int col_layer)
{
	return cantor_hash(x, cantor_hash(y, col_layer));

}

void SpatialHashMap::insert(int xi, int yi, int col_layer, CollidingShape* obj) { HashIndex[set_Hash(xi, yi, col_layer)].push_back(obj); }

std::pair<std::vector<int>, std::vector<int>> SpatialHashMap::where(CollidingShape* obj, std::vector<int> collision_layers, std::vector<int> collision_masks)
{
	const int Xmin = get_Cell(obj->get_MinMaxX().x);
	const int Xmax = get_Cell(obj->get_MinMaxX().y);
	const int Ymin = get_Cell(obj->get_MinMaxY().x);
	const int Ymax = get_Cell(obj->get_MinMaxY().y);

	int key = 0;
	std::pair<std::vector<int>, std::vector<int>> list;
	for (int indey = Ymin; indey <= Ymax; indey++)
	{
		for (int index = Xmin; index <= Xmax; index++)
		{
			for (const int layer : collision_layers)
			{
				key = set_Hash(index, indey, layer);

				HashIndex[key].push_back(obj);
				list.first.push_back(key);
			}
			for (const int layer : collision_masks)
			{
				key = set_Hash(index, indey, layer);

				list.second.push_back(key);
			}
		}
	}
	return list;
}

void SpatialHashMap::flush(CollidingShape* obj, const std::vector<int> belonging)
{
	for (int key : belonging)
	{
		auto it = std::find(HashIndex[key].begin(), HashIndex[key].end(), obj);

		while (it != HashIndex[key].end())
		{
			HashIndex[key].erase(it);
			it = std::find(HashIndex[key].begin(), HashIndex[key].end(), obj);
		}

		if (HashIndex[key].empty()) { HashIndex.erase(key); }
	}
	obj->set_HashBelonging({});
}

uint64_t SpatialHashMap::rent_UID() { return IDCounter++; }

SpatialHashMap::SpatialHashMap(float spacing_val, Vector2i length_val)
{
	Spacing = spacing_val;
	Length = length_val;
}

SpatialHashMap::~SpatialHashMap()
{
	for (auto& [key, val] : HashIndex)
	{
		for (CollidingShape* obj : val) {
			obj = nullptr;
		}
	}
};
