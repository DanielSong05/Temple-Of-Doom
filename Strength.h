#ifndef STRENGTH_INCLUDED
#define STRENGTH_INCLUDED
#include <string>
#include "Scroll.h"
class Strength:public Scroll
{
public:
	Strength(int x, int y);
	virtual ~Strength();
	virtual std::string callAction() const;

};

#endif
