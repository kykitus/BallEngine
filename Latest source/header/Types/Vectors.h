#ifndef BE_VECTORS
#define BE_VECTORS

struct Vector2f;
struct Vector2i;
struct Vector3f;
struct Vector3i;

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
	bool operator!=(Vector2f const& pos);

	Vector2f normalised();

	Vector2f() = default;
	Vector2f(float val_x, float val_y);
	Vector2f(Vector2i pos);
};

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

struct Vector3f
{
	float x, y, z;

	Vector3f operator+(Vector3f const& pos);
	Vector3f operator-(Vector3f const& pos);
	Vector3f operator*(Vector3f const& pos);
	Vector3f operator*(Vector3i const& pos);
	Vector3f operator/(Vector3f const& pos);
	Vector3f operator+(float const& pos);
	Vector3f operator*(float const& pos);
	Vector3f operator/(float const& pos);
	Vector3f operator=(float const& pos);
	Vector3f operator=(Vector3f const& pos);
	Vector3f operator+=(Vector3f const& pos);

	Vector3f normalised();

	Vector3f() = default;
	Vector3f(float val_x, float val_y, float val_z);
	Vector3f(Vector3i pos);
};

struct Vector3i
{
	int x, y, z;

	Vector3i operator+(Vector3i const& pos);
	Vector3i operator+(Vector3f const& pos);
	Vector3i operator-(Vector3i const& pos);
	Vector3i operator*(Vector3i const& pos);
	Vector3i operator*(Vector3f const& pos);
	Vector3i operator*(int const& pos);
	Vector3i operator=(int const& pos);
	Vector3i operator=(Vector3i const& pos);
	Vector3i operator+=(Vector3i const& pos);

	Vector3i() = default;
	Vector3i(int val_x, int val_y, int val_z);
	Vector3i(Vector3f pos);
};

#endif