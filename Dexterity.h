#ifndef DEXTERITY_INCLUDED
#define DEXTERITY_INCLUDED
#include <string>
#include "Scroll.h"
class Dexterity :public Scroll
{
public:
	Dexterity(int x, int y);
	virtual ~Dexterity();
	virtual std::string callAction() const;

};

#endif
