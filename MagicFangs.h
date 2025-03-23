#ifndef MAGICFANGS_INCLUDED
#define MAGICFANGS_INCLUDED
#include "Weapon.h"
#include <string>
class MagicFangs :public Weapon {
public:
	MagicFangs(int x, int y);
	virtual ~MagicFangs();
	virtual std::string callAction() const;
};
#endif // !MACE_INCLUDED#pragma once
