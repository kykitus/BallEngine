#include "WObjects/Cog.h"

#include <iostream>
#include <string>

#include "SphereCore.h"


void Cog::Ready() {}
void Cog::Tick() {}
void Cog::Render() {}
void Cog::Physics() {}

Cog& Cog::get_Child(int index) { return *Children[index]; }

void Cog::add_Child(std::shared_ptr<Cog> child) { Children.push_back(child); }

void Cog::remove_Child(int index) { Children.erase(Children.begin() + index); }

std::vector<std::shared_ptr<Cog>>& Cog::get_Children() { return Children; }


void Cog::poke(int val, Cog& caller) { if (Interaction.count(val)) { Interaction[val](caller); } else { Root->get_Logger()->push_Log("No Function Called on poke(" + std::to_string(val) + ")"); } }

bool Cog::get_IsTicking() { return IsTicking; }
void Cog::set_IsTicking(bool is) { IsTicking = is; }
bool Cog::get_IsPhysicing() { return IsPhysicing; }
void Cog::set_IsPhysicing(bool is) { IsPhysicing = is; }
