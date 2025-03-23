#include "Monster.h"
Monster::Monster(char symbol, int x, int y, int hp, int armor, int strength, int dexterity, int sleepTime, Weapon* weapon, std::string name)
	:Actor(symbol, x, y, hp, hp, armor, strength, dexterity, sleepTime, weapon), m_name(name)
{}
Monster::~Monster(){}

std::string Monster::getName() {
	return m_name;
}