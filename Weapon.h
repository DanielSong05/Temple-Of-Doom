#ifndef WEAPON_INCLUDED
#define WEAPON_INCLUDED
#include <string>
#include "GameObject.h"
class Weapon:public GameObject
{
public:
	Weapon(char symbol, std::string name, int x, int y, int dexterityBonus, int damageAmt);
	virtual ~Weapon();
	virtual std::string callAction() const = 0;
	int getDexterity() const;
	int getDamage() const;

private:
	int m_dexterityBonus;
	int m_damageAmt;
};

#endif
