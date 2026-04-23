#include "BallEngine/Elements/ButtonEntries.h"


// BUTTON ENTRY

FuncBase* Button_Entry::get_FuncRef() { return FuncRef; }

void Button_Entry::tryFunc(Node* caller) { if (CanExec) { FuncRef->get_Funct()(caller); } }
void Button_Entry::tryDest() { FuncRef->use_Dest(); }
bool Button_Entry::checkLifeTime() { return false; }

Button_Entry::Button_Entry(FuncBase* func) { if (func != nullptr) { FuncRef = func; } }

//



// BUTTON SINGLE

bool Button_Single::checkLifeTime() { if (LifeCounter <= 0) { return false; } else { LifeCounter--; return true; } }
void Button_Single::tryFunc(Node* caller) { Button_Entry::tryFunc(caller); CanExec = false; LifeCounter = 2; }

//