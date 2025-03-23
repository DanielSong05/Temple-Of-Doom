#include "Strength.h"
Strength::Strength(int x, int y)
	:Scroll('?', "scroll of strength", x, y)
{}
Strength::~Strength()
{}
std::string Strength::callAction() const {
	return "Your muscles bulge.";
}
