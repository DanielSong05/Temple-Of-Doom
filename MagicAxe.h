#ifndef MAGICAXE_INCLUDED
#define MAGICAXE_INCLUDED
#include "Weapon.h"
#include <string>
class MagicAxe:public Weapon {
public:
	MagicAxe(int x, int y);
	virtual ~MagicAxe();
	virtual std::string callAction() const;
};
#endif // !MACE_INCLUDED#pragma once
