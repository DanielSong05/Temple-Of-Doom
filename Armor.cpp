#include "Armor.h"
Armor::Armor(int x, int y)
	:Scroll('?', "scroll of enhance armor", x, y)
{}
Armor::~Armor()
{}
std::string Armor::callAction() const {
	return "Your armor glows blue.";
}
