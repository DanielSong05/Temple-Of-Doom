#include "Health.h"
Health::Health(int x, int y)
	:Scroll('?', "scroll of enhance health", x, y)
{}
Health::~Health()
{}
std::string Health::callAction() const {
	return "You feel your heart beating stronger.";
}
