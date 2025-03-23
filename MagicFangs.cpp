#include "MagicFangs.h"
MagicFangs::MagicFangs(int x, int y)
	:Weapon(')', "magic fangs", x, y, 3, 2)
{}
MagicFangs::~MagicFangs() {}
std::string MagicFangs::callAction() const {
	return "strikes magic fangs at";
}

