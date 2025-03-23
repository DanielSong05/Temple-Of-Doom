#ifndef TELEPORTATION_INCLUDED
#define TELEPORTATION_INCLUDED
#include <string>
#include "Scroll.h"
class Teleportation:public Scroll
{
public:
	Teleportation(int x, int y);
	virtual ~Teleportation();
	virtual std::string callAction() const;

};

#endif
