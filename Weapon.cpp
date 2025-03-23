#include "Weapon.h"

Weapon::Weapon(char symbol, std::string name, int x, int y, int dexterityBonus, int damageAmt)
	:GameObject(symbol, name, x, y), m_dexterityBonus(dexterityBonus), m_damageAmt(damageAmt)
{}
Weapon::~Weapon(){}

int Weapon::getDexterity() const {
	return m_dexterityBonus;
}
int Weapon::getDamage() const{
	return m_damageAmt;
}