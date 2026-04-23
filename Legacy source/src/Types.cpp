#include "BallEngine/Types.h"
#include "BallEngine/EngineCore.h"

// SGN

template <typename T> 
int sgn(T val)
{
	return (T(0) < val) - (val < T(0));
}

template int sgn<int>(int val);
template int sgn<float>(float val);

//



// TEXT TO INT

std::vector<int> resolve_TextIntArray(std::string text)
{
	std::vector<int> list;
	short int last = 0;
	int num = 0;
	for (int type = 0; type <= text.length(); type++)
	{
		if (text[type] == 44)
		{
			num = std::stoi(text.substr(last, type - last));
			last = type + 1;
			list.push_back(num);
		}
	}
	return list;
}

//



// CANTOOR HASH

int cantor_hash(int x, int y) { return 0.5 * (x + y) * (x + y + 1) + y; }

//



///// VECTOR 2d FLOAT

Vector2f Vector2f::operator+(Vector2f const& pos)
{
	return {x + pos.x, y + pos.y};
}
Vector2f Vector2f::operator-(Vector2f const& pos)
{
	return { x - pos.x, y - pos.y };
}
Vector2f Vector2f::operator*(Vector2f const& pos)
{
	return { x * pos.x, y * pos.y };
}
Vector2f Vector2f::operator*(Vector2i const& pos)
{
	return { x * pos.x, y * pos.y };
}
Vector2f Vector2f::operator/(Vector2f const& pos)
{
	return { x / pos.x, y / pos.y };
}
Vector2f Vector2f::operator+(float const& pos)
{
	return { x + pos, y + pos };
}
Vector2f Vector2f::operator*(float const& pos)
{
	return { x * pos, y * pos};
}
Vector2f Vector2f::operator/(float const& pos)
{
	return { x / pos, y / pos };
}
Vector2f Vector2f::operator=(float const& pos)
{
	this->x = pos;
	this->y = pos;
	return *this;
}
Vector2f Vector2f::operator=(Vector2f const& pos)
{
	this->x = pos.x;
	this->y = pos.y;
	return *this;
}
Vector2f Vector2f::operator+=(Vector2f const& pos)
{
	this->x += pos.x;
	this->y += pos.y;
	return *this;
}



Vector2f Vector2f::normalised()
{
	float length = sqrt(pow(x, 2) + pow(y, 2));
	return { x /= length, y /= length };
}

Vector2f::Vector2f(float val_x, float val_y) :
	x(val_x),
	y(val_y) {}

Vector2f::Vector2f(Vector2i pos) :
	x(pos.x),
	y(pos.y) {}

/////



///// VECTOR 2D INT

Vector2i Vector2i::operator+(Vector2i const& pos)
{
	return { x + pos.x, y + pos.y };
}
Vector2i Vector2i::operator+(Vector2f const& pos)
{
	return { x + (int)pos.x, y + (int)pos.y };
}
Vector2i Vector2i::operator-(Vector2i const& pos)
{
	return { x - pos.x, y - pos.y };
}
Vector2i Vector2i::operator*(Vector2i const& pos)
{
	return { x * pos.x, y * pos.y };
}
Vector2i Vector2i::operator*(Vector2f const& pos)
{
	return { x * (int)pos.x, y * (int)pos.y };
}
Vector2i Vector2i::operator*(int const& pos)
{
	return { x * pos, y * pos };
}
Vector2i Vector2i::operator=(int const& pos)
{
	this->x = pos;
	this->y = pos;
	return *this;
}
Vector2i Vector2i::operator=(Vector2i const& pos)
{
	this->x = pos.x;
	this->y = pos.y;
	return *this;
}
Vector2i Vector2i::operator+=(Vector2i const& pos)
{
	this->x += pos.x;
	this->y += pos.y;
	return *this;
}

Vector2i::Vector2i(int val_x, int val_y) :
	x(val_x),
	y(val_y) {}

Vector2i::Vector2i(Vector2f pos) :
	x(pos.x),
	y(pos.y) {}

/////

