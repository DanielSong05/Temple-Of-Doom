#include "ShortSword.h"
ShortSword::ShortSword()
	:Weapon(')',"short sword", 0, 0, 0, 2)
{}
ShortSword::ShortSword(int x, int y)
	:Weapon(')', "short sword", x, y, 0, 2)
{}
ShortSword::~ShortSword() {}
std::string ShortSword::callAction() const {
	return "slashes short sword at";
}