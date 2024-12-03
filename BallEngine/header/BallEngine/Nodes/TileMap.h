#ifndef SDL_ENGINE_TILES
#define SDL_ENGINE_TILES

#include "BallEngine/Types.h"
#include "Nodes.h"
#include "BallEngine/Components/BasicComponents.h"


/////

class Tile_Class : public Effigy
{
public:

	//Collision_Rect_Comp_Array Body;

	std::unordered_map<int, std::unordered_map<int, Colliding_Tile>>& get_Tiles();

	uint8_t get_NameID();
	void set_NameID(uint8_t val);
	Vector2i get_MinMaxX();
	Vector2i get_MinMaxY();
	void set_MinMaxX(Vector2i val);
	void set_MinMaxy(Vector2i val);
	void update_MinMaxX(int val);
	void update_MinMaxY(int val);

	bool get_IsVisible();
	void set_IsVisible(bool val);

	CollisionPlane& get_CollisionMap();

	virtual void process_delta(Mask& parent);

	Tile_Class(uint8_t name, std::pair<std::vector<int>, std::vector<int>> col_layers);

private:

	uint8_t NameID;

	Vector2i MinMaxX = { 0, 0 };
	Vector2i MinMaxY = { 0, 0 };

	bool IsVisible;

	CollisionPlane CollisionMap;

	std::unordered_map<int, std::unordered_map<int, Colliding_Tile>> Tiles;
};

/////

class Tile
{
public:

	Vector2i get_PatternChunk();
	void set_PatternChunk(Vector2i pos);

	Tile() = default;
	explicit Tile(Vector2i pattern);

protected:
	
	Vector2i PatternChunk;

};

/////



//

class Colliding_Tile : public Tile 
{
public:

	Rectangle_Component& get_Chunk();
	void set_Chunk(Rectangle_Component* val, Mask& parent);
	void delete_Chunk();

	using Tile::Tile;
	Colliding_Tile(Vector2i pattern, Vector2f pos, Vector2f size, Node& owner);

protected:

	std::shared_ptr<Rectangle_Component> Chunk;

};

//



///// TILE MAP CREATOR

class Tile_Map : public Effigy
{
public:

	Visual_Component_Rect Canva;

	std::vector<Tile_Class>& get_TileLayers();
	Tile_Class& get_TileLayer(int id);

	Vector2f get_TileSize();
	void set_TileSize(Vector2f val);

	void DEMO_read_Class(std::string class_path);
	void read_Map(std::string path);

	void simplify_Map(Tile_Class map);
	void print_Map(int layer);
	void seek_TileGroup(int starting_point, std::vector<int> compare); // used only in simplify_map()

	virtual void process_delta() override;
	virtual void render() override;

	Tile_Map() = default;
	Tile_Map(uint8_t parent, std::string class_path, std::string path, std::string texture_path);

	virtual ~Tile_Map() = default;

	
protected:

	Vector2f TileSize = { 32.0f, 32.0f };
	Vector2f ImgSize = { 100.0f, 100.0f };

	std::vector<Tile_Class> TileLayers;


};

/////

#endif