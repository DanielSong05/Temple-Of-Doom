#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED
#include "Actor.h"
#include "GameObject.h"
#include "Game.h"
#include "Monster.h"
#include <vector>
class Player:public Actor{
public:
	Player();
	Player(int x, int y);
	virtual ~Player();
	void movePlayer(int dx, int dy, Game& game);
	void storeObject(int x, int y, Game& game);
	const std::vector<GameObject*>& getInventory() const;
	void displayInventory();
	void wieldWeapon(char c, Game& game);
	void readScroll(char c, Game& game);
	void attackMonster(Monster& monster, Game& game);
private:
	bool canMoveTo(int x, int y, Game& game);
	std::vector<GameObject*> m_inventory;
};

#endif
