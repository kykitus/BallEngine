#include "BallEngine/DataStructures/ControlJournal.h"

void Control_Journal::addEntry(Button_Entry* new_entry) { Entries[Counter] = std::unique_ptr<Button_Entry>(new_entry); Counter++; }

void Control_Journal::update() 
{
	if (Entries.size() != 0) 
	{
		std::vector<long int> for_deletion;
		for (auto& [key, value] : Entries) 
		{
			if (!value->checkLifeTime()) { for_deletion.push_back(key); };
		}
		for (long int id : for_deletion) { Entries[id]->get_FuncRef()->set_Id(0); Entries.erase(id); }
	}
}

bool Control_Journal::isQueueEmpty() { return Entries.empty(); }
