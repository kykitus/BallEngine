#ifndef PACMAN_DEBUG
#define PACMAN_DEBUG

#define PRINT std::cout <<
#define PRINT_ERROR std::cerr <<

typedef std::function<void()>  var_func;

enum state
{
	S_CEILING,
	S_FLOOR,
	S_LEFT,
	S_RIGHT
};

enum min_max
{
	MIN,
	MAX
};

enum class OBJ_Type
{
	Node,

};

enum shape_complexity
{
	DOT,
	RAY,
	BOX,
	CIRCLE,
	CONVEX
};

#endif
