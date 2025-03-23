#include "MagicAxe.h"
MagicAxe::MagicAxe(int x, int y)
	:Weapon(')', "magic axe", x, y, 5, 5)
{}
MagicAxe::~MagicAxe() {}
std::string MagicAxe::callAction() const {
	return "chops magic axe at";
}