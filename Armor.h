#ifndef ARMOR_INCLUDED
#define ARMOR_INCLUDED
#include <string>
#include "Scroll.h"
class Armor:public Scroll
{
public:
	Armor(int x, int y);
	virtual ~Armor();
	virtual std::string callAction() const;

};

#endif
