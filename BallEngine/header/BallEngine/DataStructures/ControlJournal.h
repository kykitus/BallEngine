#ifndef SDL_ENGINE_CONTROLJOURNAL
#define SDL_ENGINE_CONTROLJOURNAL


#include "BallEngine/Elements/ButtonEntries.h"

// CONTROL JOURNAL

class Control_Journal
{
public:

	//
	template <class T = Button_Entry>
	void request(Node* caller, FuncBase* func)
	{
		if (func->get_Id() == 0)
		{
			Counter++;
			func->set_Id(Counter);
			addEntry(new T(func));
		}
		Entries[func->get_Id()]->tryFunc(caller);
	}
	//

	void addEntry(Button_Entry* new_entry);

	void update();
	bool isQueueEmpty();

	Control_Journal() = default;
	~Control_Journal() = default;

private:

	std::unordered_map<long int, std::unique_ptr<Button_Entry>> Entries;

	long int Counter = 1;

};

//


#endif