#include "BallEngine/Elements/Func.h"
#include "BallEngine/EngineCore.h"
#include "BallEngine/DataStructures/ControlJournal.h"

#define CALL_ACTION_REG Owner->get_Mask().get_ActionReg()

// FUNC BASE

long int& FuncBase::get_Id() { return Id; }
void FuncBase::set_Id(long int val) { Id = val; }
std::function<void(Node*)>& FuncBase::get_Funct() { return Funct; }

void FuncBase::use(Node* caller) { CALL_ACTION_REG.request(caller, this); }
void FuncBase::replace(std::function<void(Node*)> val) { Funct = val; }
void FuncBase::use_Dest() { Destructor(); }
void FuncBase::replace_Destructor(std::function<void()> val) { Destructor = val; }

FuncBase::FuncBase() : Funct(0), Owner(nullptr) {}
FuncBase::FuncBase(std::function<void(Node*)> func, Node* owner) : Funct(func), Owner(owner) {}

//

void FNormal::use(Node* caller) { CALL_ACTION_REG.request<Button_Entry>(caller, this); }

void FSingle::use(Node * caller) { CALL_ACTION_REG.request<Button_Single>(caller, this); }


