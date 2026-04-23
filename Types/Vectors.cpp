#include "Types/Vectors.h"

#include <cmath>

// Vector2f

Vector2f Vector2f::operator+(Vector2f const& pos)
{
	return { x + pos.x, y + pos.y };
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
	return { x * pos, y * pos };
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

bool Vector2f::operator!=(Vector2f const& pos)
{
	if (this->x == pos.x && this->y == pos.y) { return true; }
	return false;
}



Vector2f Vector2f::normalised()
{
	float length = sqrt(pow(x, 2) + pow(y, 2));
	return { x /= length, y /= length };
}

Vector2f::Vector2f(float val_x, float val_y) :
	x(val_x),
	y(val_y) {
}

Vector2f::Vector2f(Vector2i pos) :
	x(pos.x),
	y(pos.y) {
}

//


// Vector2i

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
	y(val_y) {
}

Vector2i::Vector2i(Vector2f pos) :
	x(pos.x),
	y(pos.y) {
}

//

// Vector3f

Vector3f Vector3f::operator+(Vector3f const& pos)
{
	return { x + pos.x, y + pos.y, z + pos.z};
}
Vector3f Vector3f::operator-(Vector3f const& pos)
{
	return { x - pos.x, y - pos.y, z - pos.z };
}
Vector3f Vector3f::operator*(Vector3f const& pos)
{
	return { x * pos.x, y * pos.y, z * pos.z };
}
Vector3f Vector3f::operator*(Vector3i const& pos)
{
	return { x * pos.x, y * pos.y, z * pos.z };
}
Vector3f Vector3f::operator/(Vector3f const& pos)
{
	return { x / pos.x, y / pos.y, z / pos.z };
}
Vector3f Vector3f::operator+(float const& pos)
{
	return { x + pos, y + pos, z + pos };
}
Vector3f Vector3f::operator*(float const& pos)
{
	return { x * pos, y * pos, z * pos };
}
Vector3f Vector3f::operator/(float const& pos)
{
	return { x / pos, y / pos, z / pos };
}
Vector3f Vector3f::operator=(float const& pos)
{
	this->x = pos;
	this->y = pos;
	this->z = pos;
	return *this;
}
Vector3f Vector3f::operator=(Vector3f const& pos)
{
	this->x = pos.x;
	this->y = pos.y;
	this->z = pos.z;
	return *this;
}
Vector3f Vector3f::operator+=(Vector3f const& pos)
{
	this->x += pos.x;
	this->y += pos.y;
	this->z += pos.z;
	return *this;
}



Vector3f Vector3f::normalised()
{
	float length = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	return { x /= length, y /= length, z/= length };
}

Vector3f::Vector3f(float val_x, float val_y, float val_z) :
	x(val_x),
	y(val_y),
	z(val_z) {}

Vector3f::Vector3f(Vector3i pos) :
	x(pos.x),
	y(pos.y),
	z(pos.z) {}

//


// Vector2i

Vector3i Vector3i::operator+(Vector3i const& pos)
{
	return { x + pos.x, y + pos.y, z + pos.z };
}
Vector3i Vector3i::operator+(Vector3f const& pos)
{
	return { x + (int)pos.x, y + (int)pos.y, z + (int)pos.z };
}
Vector3i Vector3i::operator-(Vector3i const& pos)
{
	return { x - pos.x, y - pos.y, z - pos.z };
}
Vector3i Vector3i::operator*(Vector3i const& pos)
{
	return { x * pos.x, y * pos.y, z * pos.z };
}
Vector3i Vector3i::operator*(Vector3f const& pos)
{
	return { x * (int)pos.x, y * (int)pos.y, z * (int)pos.z };
}
Vector3i Vector3i::operator*(int const& pos)
{
	return { x * pos, y * pos, z * pos };
}
Vector3i Vector3i::operator=(int const& pos)
{
	this->x = pos;
	this->y = pos;
	this->z = pos;
	return *this;
}
Vector3i Vector3i::operator=(Vector3i const& pos)
{
	this->x = pos.x;
	this->y = pos.y;
	this->z = pos.z;
	return *this;
}
Vector3i Vector3i::operator+=(Vector3i const& pos)
{
	this->x += pos.x;
	this->y += pos.y;
	this->z += pos.z;
	return *this;
}

Vector3i::Vector3i(int val_x, int val_y, int val_z) :
	x(val_x),
	y(val_y),
	z(val_y) {}

Vector3i::Vector3i(Vector3f pos) :
	x(pos.x),
	y(pos.y),
	z(pos.z) {}

//