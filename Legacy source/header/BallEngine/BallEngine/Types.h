#ifndef PACMAN_TYPES
#define PACMAN_TYPES

#include "BallEngine/Classes.h"

template <typename T>
int sgn(T val);


std::vector<int> resolve_TextIntArray(std::string text);

// Returns hash value out of two numbers
int cantor_hash(int x, int y);


///// VECTOR 2D FLOAT

struct Vector2f
{
	float x, y;

	Vector2f operator+(Vector2f const& pos);
	Vector2f operator-(Vector2f const& pos);
	Vector2f operator*(Vector2f const& pos);
	Vector2f operator*(Vector2i const& pos);
	Vector2f operator/(Vector2f const& pos);
	Vector2f operator+(float const& pos);
	Vector2f operator*(float const& pos);
	Vector2f operator/(float const& pos);
	Vector2f operator=(float const& pos);
	Vector2f operator=(Vector2f const& pos);
	Vector2f operator+=(Vector2f const& pos);

	Vector2f normalised();

	Vector2f() = default;
	Vector2f(float val_x, float val_y);
	Vector2f(Vector2i pos);
};

/////



///// VECTOR 2D INT

struct Vector2i
{
	int x, y;

	Vector2i operator+(Vector2i const& pos);
	Vector2i operator+(Vector2f const& pos);
	Vector2i operator-(Vector2i const& pos);
	Vector2i operator*(Vector2i const& pos);
	Vector2i operator*(Vector2f const& pos);
	Vector2i operator*(int const& pos);
	Vector2i operator=(int const& pos);
	Vector2i operator=(Vector2i const& pos);
	Vector2i operator+=(Vector2i const& pos);

	Vector2i() = default;
	Vector2i(int val_x, int val_y);
	Vector2i(Vector2f pos);
};

/////


#endif
