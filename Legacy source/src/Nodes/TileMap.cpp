#include "BallEngine/Nodes/TileMap.h"
#include "BallEngine/Nodes/Nodes.h"
#include "BallEngine/Global.h"
#include "BallEngine/Components/BasicComponents.h"
#include "BallEngine/DataStructures/DataStructures.h"
#include "BallEngine/DataStructures/ResourceRepositiory.h"
#include "BallEngine/EngineCore.h"

// TILE CLASS

std::unordered_map<int, std::unordered_map<int, Colliding_Tile>>& Tile_Class::get_Tiles() { return Tiles; }

uint8_t Tile_Class::get_NameID() { return NameID; }
void Tile_Class::set_NameID(uint8_t val) { NameID = val; }

Vector2i Tile_Class::get_MinMaxX() { return MinMaxX; }
Vector2i Tile_Class::get_MinMaxY() { return MinMaxY; }
void Tile_Class::set_MinMaxX(Vector2i val) { MinMaxX = val; }
void Tile_Class::set_MinMaxy(Vector2i val) { MinMaxY = val; }
void Tile_Class::update_MinMaxX(int val) { MinMaxX.x = (val < MinMaxX.x) ? val : MinMaxX.x; MinMaxX.y = (val > MinMaxX.y) ? val : MinMaxX.y; }
void Tile_Class::update_MinMaxY(int val) { MinMaxY.x = (val < MinMaxY.x) ? val : MinMaxY.x; MinMaxY.y = (val > MinMaxY.y) ? val : MinMaxY.y; }


bool Tile_Class::get_IsVisible() { return IsVisible; }
void Tile_Class::set_IsVisible(bool val) { IsVisible = val; }

CollisionPlane& Tile_Class::get_CollisionMap() { return CollisionMap; }

void Tile_Class::process_delta(Mask& parent) {}

Tile_Class::Tile_Class(uint8_t name, std::pair<std::vector<int>,std::vector<int>> col_layers) :
	NameID(name),
	CollisionMap(col_layers)
{}

// TILE

Vector2i Tile::get_PatternChunk() { return PatternChunk; }
void Tile::set_PatternChunk(Vector2i pos) { PatternChunk = pos; }

Tile::Tile(Vector2i pattern) : PatternChunk(pattern) {}

//



//

Rectangle_Component& Colliding_Tile::get_Chunk() { if (Chunk == nullptr) { std::cerr << "Tile Chunk doesn't exist right now"; } else { return *Chunk; } }
void Colliding_Tile::set_Chunk(Rectangle_Component* val, Mask& parent)
{
	if (Chunk != nullptr) { Chunk.get()->destructor(parent); }
	Chunk = std::make_shared<Rectangle_Component>(*val);
}
void Colliding_Tile::delete_Chunk() { Chunk = nullptr; }

Colliding_Tile::Colliding_Tile(Vector2i pattern, Vector2f pos, Vector2f size, Node& owner) : Tile(pattern), Chunk(new Rectangle_Component(pos, size, owner)) {}

//



// TILEMAP 

std::vector<Tile_Class>& Tile_Map::get_TileLayers() { return TileLayers; }
Tile_Class& Tile_Map::get_TileLayer(int id) { return TileLayers[id]; }
Vector2f Tile_Map::get_TileSize() { return TileSize; }
void Tile_Map::set_TileSize(Vector2f val) { TileSize = val; }

void Tile_Map::DEMO_read_Class(std::string class_path) 
{
	int name_id = 0;
	std::string collision;

	std::ifstream found(class_path, std::ios::in);
	char peek;

	while (!found.eof())
	{

		peek = found.peek();
		if (peek == '#' || peek == '\n') { found.ignore(256, '\n'); continue; }
		std::getline(found, collision, '\n');


		TileLayers.push_back(Tile_Class(
			name_id,
			{ resolve_TextIntArray(collision), resolve_TextIntArray(collision) }
		));
		name_id++;
	}
	found.close();
}

void Tile_Map::read_Map(std::string path)
{
	int name_id = 0;
	std::pair<std::string, std::string> cord;
	std::pair<std::string, std::string> pattern;
	Vector2i cords = { 0,0 };

	std::ifstream found(path, std::ios::in);
	char peek;

	while (!found.eof())
	{
		peek = found.peek();
		if (peek == '\n') { found.ignore(256, '\n'); name_id++; continue; }
		std::getline(found, cord.first, '\t');
		std::getline(found, cord.second, '\t');
		std::getline(found, pattern.first, '\t');
		std::getline(found, pattern.second, '\n');

		cords = { std::stoi(cord.first), std::stoi(cord.second) };

		TileLayers[name_id].get_Tiles()[cords.x][cords.y] = Colliding_Tile
		(
			Vector2i{ std::stoi(pattern.first), std::stoi(pattern.second) }
		);

		TileLayers[name_id].update_MinMaxX(cords.x);
		TileLayers[name_id].update_MinMaxY(cords.y);
	}
	found.close();

	for (Tile_Class map : TileLayers) 
	{
		simplify_Map(map);
	}
}

void Tile_Map::simplify_Map(Tile_Class map) // it requires copy of this map
{
	bool stop = 0;
	Vector2i max = { 0, 0 }; // max right/down borders of rectangular mass
	Rectangle_Component* new_box = nullptr;

	for (int index_x = map.get_MinMaxX().x; index_x <= map.get_MinMaxX().y; index_x++)
	{
		for (int index_y = map.get_MinMaxY().x; index_y <= map.get_MinMaxY().y; index_y++)
		{
			if (map.get_Tiles()[index_x].count(index_y))  // seek new starting tile
			{
				stop = false;
				max = { index_x, index_y };
				while (map.get_Tiles()[index_x].count(max.y)) { max.y++; } // look for lowest existing point possible
				max.y--;
				while (map.get_Tiles()[max.x].count(index_y) && !stop)
				{
					for (int ycheck = index_y; ycheck <= max.y; ycheck++) 
					{

						if (!map.get_Tiles()[max.x].count(ycheck)) { stop = true; break; }

					}
					if (!stop) { max.x++; } // look for furthest point to the right by checking top-down lower points
				}
				max.x--;
				// create box from min-max coordinates
				new_box = new Rectangle_Component
				(
					Vector2f(index_x, index_y) * TileSize + Position,
					{ (max.x - index_x + 1) * TileSize.x, (max.y - index_y + 1) * TileSize.y },
					TileLayers[map.get_NameID()].get_CollisionMap().get_CollisionLayers(),
					TileLayers[map.get_NameID()].get_CollisionMap().get_CollisionMasks(),
					get_Mask(),
					*this
				);

				for (int x = index_x; x <= max.x; x++)
				{
					for (int y = index_y; y <= max.y; y++)
					{
						TileLayers[map.get_NameID()].get_Tiles()[x][y].set_Chunk(new_box, get_Mask()); // assign pointers to box on every belonging tile
						map.get_Tiles()[x].erase(y); // delete tiles from copy of map to prevent repetition
						if (map.get_Tiles()[x].empty()) 
						{
							map.get_Tiles().erase(x);
						}
					}
				}
			}
		}
	}
}

void Tile_Map::print_Map(int layer) 
{

	/*for (auto [a, d] : TileLayers[layer].get_Tiles())
	{
		for (auto [b, e] : d)
		{
			GPU_Rect* ua = &e.get_Chunk().get_Box().get_Rect();
			GPU_BlitRect(&Root.get_Renderer(), ua);
		}
	}*/
}


void Tile_Map::process_delta()
{
}

void Tile_Map::render()
{

	GPU_Rect Dummy;


	Dummy.w = TileSize.x;
	Dummy.h = TileSize.y;

	GPU_Rect snap;

	snap.w = ImgSize.x;
	snap.h = ImgSize.y;
	for (Tile_Class map : TileLayers)
	{
		if (!map.get_IsVisible()) { continue; }
		for (const auto& [keyX, X] : map.get_Tiles())
		{
			for (auto [keyY, Y] : X)
			{
				Dummy.x = keyX * TileSize.x + Position.x + Root->get_CameraMod().x;
				Dummy.y = keyY * TileSize.y + Position.y + Root->get_CameraMod().y;

				snap.x = ImgSize.x * Y.get_PatternChunk().x;
				snap.y = ImgSize.y * Y.get_PatternChunk().y;

				GPU_BlitRect(Canva.get_Texture(), &snap, &Root->get_Renderer(), &Dummy);

			}
		}
	}
}


Tile_Map::Tile_Map(uint8_t parent, std::string class_path, std::string map_path, std::string texture_path) : Node(parent)
{
	Canva.set_TexturePath(texture_path);
	Canva.set_Texture(get_Mask().get_TextureRep().request(Canva.get_TexturePath()));
	DEMO_read_Class(class_path);
	read_Map(map_path);
}

//