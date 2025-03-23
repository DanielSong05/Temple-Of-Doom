#include "Teleportation.h"
Teleportation::Teleportation(int x, int y)
	:Scroll('?', "scroll of teleportation", x, y)
{}
Teleportation::~Teleportation()
{}
std::string Teleportation::callAction() const{
	return "You feel your body wrenched in space and time.";
}
