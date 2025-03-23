#ifndef SCROLL_INCLUDED
#define SCROLL_INCLUDED
#include <string>
#include "GameObject.h"
class Scroll :public GameObject
{
public:
	Scroll(char symbol, std::string name, int x, int y);
	virtual ~Scroll();
	virtual std::string callAction() const = 0;
	
};

#endif
