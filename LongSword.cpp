#include "LongSword.h"
LongSword::LongSword(int x, int y)
	:Weapon(')', "long sword", x, y, 2, 4)
{}
LongSword::~LongSword() {}
std::string LongSword::callAction() const {
	return "swings long sword at";
}