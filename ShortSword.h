#ifndef SHORTSWORD_INCLUDED
#define SHORTSWORD_INCLUDED
#include "Weapon.h"
#include <string>
class ShortSword:public Weapon {
public:
	ShortSword();
	ShortSword(int x, int y);
	virtual ~ShortSword();
	virtual std::string callAction() const;
};
#endif // !MACE_INCLUDED#pragma once
