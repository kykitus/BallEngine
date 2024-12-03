#include "BallEngine/DataStructures/DataStructures.h"
#include "BallEngine/Elements/CollisionPhysics.h"


// SPATIAL HASH MAP

bool Spatial_Hash_Map::check_HashMapCell(float key) { return HashIndex.count(key); }

std::vector<Colliding_Shape*> Spatial_Hash_Map::get_HashMapCell(float key) { return HashIndex[key]; }

size_t Spatial_Hash_Map::get_HashMapSize()
{
	return HashIndex.size();
}

int Spatial_Hash_Map::get_Cell(float val) { return floor(val / Spacing); }

const int Spatial_Hash_Map::set_Hash(float x, float y, int col_layer)
{
	return cantor_hash(x, cantor_hash(y, col_layer));

}

void Spatial_Hash_Map::insert(int xi, int yi, int col_layer, Colliding_Shape* obj) { HashIndex[set_Hash(xi, yi, col_layer)].push_back(obj); }

std::pair<std::vector<int>, std::vector<int>> Spatial_Hash_Map::where(Colliding_Shape* obj, std::vector<int> collision_layers, std::vector<int> collision_masks)
{
	const int Xmin = get_Cell(obj->get_MinMaxX().x);
	const int Xmax = get_Cell(obj->get_MinMaxX().y);
	const int Ymin = get_Cell(obj->get_MinMaxY().x);
	const int Ymax = get_Cell(obj->get_MinMaxY().y);

	int key;
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

void Spatial_Hash_Map::flush(Colliding_Shape* obj, const std::vector<int> belonging)
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

Spatial_Hash_Map::Spatial_Hash_Map(float spacing_val, Vector2i length_val)
{
	Spacing = spacing_val;
	Length = length_val;
}

Spatial_Hash_Map::~Spatial_Hash_Map() 
{
	for (auto& [key, val] : HashIndex) 
	{
		for (Colliding_Shape* obj : val) {
			obj = nullptr;
		}
	}
};

//