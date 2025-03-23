#ifndef MONSTER_INCLUDED
#define MONSTER_INCLUDED
#include "Actor.h"
#include "Player.h"
class Game;
class Monster :public Actor {
public:
	Monster(char symbol, int x, int y, int hp, int armor, int strength, int dexterity, int sleepTime, Weapon* weapon, std::string name);
	virtual ~Monster();
	virtual void turn(Game& game) = 0;
	virtual void attackPlayer(Game& game) = 0;
	std::string getName();
private:
	std::string m_name;
};



#endif
