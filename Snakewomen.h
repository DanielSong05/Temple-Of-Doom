#ifndef SNAKEWOMEN_INCLUDED
#define SNAKEWOMEN_INCLUDED
#include "Monster.h"
#include "Player.h"
#include "Game.h"
class Snakewomen :public Monster {
public:
	Snakewomen(int x, int y);
	virtual ~Snakewomen();
	virtual void turn(Game& game);
	virtual void attackPlayer(Game& game);
private:
	void moveCloserToPlayer(Game& game);
	bool canMoveTo(int x, int y, Game& game);
};
#endif