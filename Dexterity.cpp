#include "Dexterity.h"
Dexterity::Dexterity(int x, int y)
	:Scroll('?', "scroll of enhance dexterity", x, y)
{}
Dexterity::~Dexterity()
{}
std::string Dexterity::callAction() const {
	return "You feel like less of a klutz.";
}
