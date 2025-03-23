#ifndef LONGSWORD_INCLUDED
#define LONGSWORD_INCLUDED
#include "Weapon.h"
#include <string>
class LongSword:public Weapon {
public:
	LongSword(int x, int y);
	virtual ~LongSword();
	virtual std::string callAction() const;
};
#endif // !MACE_INCLUDED#pragma once
