#ifndef ACTOR_INCLUDED
#define ACTOR_INCLUDED
#include "GameObject.h"
#include "Weapon.h"
#include "Scroll.h"
#include "Game.h"
#include "utilities.h"
#include "ShortSword.h"
#include "LongSword.h"
#include "Mace.h"
#include "MagicAxe.h"
#include "MagicFangs.h"
class Weapon;
class Actor {
public:
	Actor(char symbol, int x, int y, int hp, int maxHP, int armor, int strength, int dexterity, int sleepTime, Weapon* weapon);
	virtual ~Actor();
	char getSymbol()const;
	int getHitPoints()const;
	void changeHitPoints(int hp);
	int getMaxHitPoints()const;
	void changeMaxHitPoints(int maxhp);
	int getArmor()const;
	void changeArmor(int armor);
	int getStrength()const;
	void changeStrength(int strength);
	int getDexterity()const;
	void changeDexterity(int dexterity);
	int getSleepTime()const;
	void changeSleepTime(int sleepTime);
	Weapon* getWeapon()const;
	void changeWeapon(Weapon* weapon);
	void changeX(int val);
	void changeY(int val);
	int getX() const;
	int getY() const;
	void setPosition(int x, int y);
private:
	char m_symbol;
	int m_Actx;
	int m_Acty;
	int m_hitPoints;
	int m_maxHitPoints;
	int m_armor;
	int m_strength;
	int m_dexterity;
	int m_sleepTime;
	Weapon* m_weapon;
};
#endif
