#include "Mace.h"

Mace::Mace(int x, int y)
	:Weapon(')', "mace", x, y, 0, 2)
{}
Mace::~Mace(){}
std::string Mace::callAction() const{
	return "swings mace at";
}