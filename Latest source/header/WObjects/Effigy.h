#ifndef BE_EFFIGY
#define BE_EFFIGY

#include <unordered_map>
#include <map>
#include <functional>

#include "WObjects/Cog.h"
#include "Types/Vectors.h"
#include "Types/Asset.h"

class Effigy : public Cog
{
public:


	Vector2f& get_Position();
	virtual void set_Position(Vector2f val);
	

	Effigy() = default;
	virtual ~Effigy();

protected:


	Vector2f Position = { 23.0f, 23.0f }; //logic position in the center of the body


};

#endif