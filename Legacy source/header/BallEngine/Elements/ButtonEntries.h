#ifndef SDL_ENGINE_BUTTON_ENTRIES
#define SDL_ENGINE_BUTTON_ENTRIES

#include "BallEngine/Elements/Func.h"

// BUTTON ENTRY

class Button_Entry
{
public:

	FuncBase* get_FuncRef();

	virtual void tryFunc(Node* caller);
	virtual void tryDest();
	virtual bool checkLifeTime();

	Button_Entry(FuncBase* func);
	virtual ~Button_Entry() = default;

protected:

	FuncBase* FuncRef;
	bool CanExec = true;

};

//

class Button_Single : public Button_Entry 
{
public:
	using Button_Entry::Button_Entry;

	virtual bool checkLifeTime() override;
	virtual void tryFunc(Node* caller) override;

	~Button_Single() = default;

protected:

	int LifeCounter = 2;

};


#endif