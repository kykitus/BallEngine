#ifndef SDL_ENGINE_FUNC
#define SDL_ENGINE_FUNC

#include "BallEngine/Classes.h"

class FuncBase 
{
public:

	long int& get_Id();
	void set_Id(long int val);
	std::function<void(Node*)>& get_Funct();

	virtual void use(Node* caller);
	void replace(std::function<void(Node*)> val);
	void use_Dest();
	void replace_Destructor(std::function<void()> val);

	FuncBase();
	FuncBase(std::function<void(Node*)> func, Node* owner);

protected:

	std::function<void(Node*)> Funct = [](Node* caller) {PRINT "no functionality used here yet"; };
	std::function<void()> Destructor = []() {};
	long int Id = 0;
	Node* Owner;

};

class FNormal : public FuncBase
{
public:
	using FuncBase::FuncBase;

	void use(Node* caller) override;
};


class FSingle : public FuncBase
{
public:
	using FuncBase::FuncBase;

	void use(Node* caller) override;
};



// CASTING MOLD FUNCTION

template <class Type>
class Func : public Type// Base struct for making functions protected by repetitive conditions
{ using Type::Type; };

//

#endif