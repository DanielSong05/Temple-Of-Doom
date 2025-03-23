#ifndef MACE_INCLUDED
#define MACE_INCLUDED
#include "Weapon.h"
#include <string>
class Mace:public Weapon {
public:
	Mace(int x, int y);
	virtual ~Mace();
	virtual std::string callAction() const;
};
#endif // !MACE_INCLUDED

