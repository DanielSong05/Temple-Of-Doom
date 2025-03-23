#ifndef HEALTH_INCLUDED
#define HEALTH_INCLUDED
#include <string>
#include "Scroll.h"
class Health:public Scroll
{
public:
	Health(int x, int y);
	virtual ~Health();
	virtual std::string callAction() const;

};

#endif
