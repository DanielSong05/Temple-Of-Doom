#ifndef BOGEYMAN_INCLUDED
#define BOGEYMAN_INCLUDED
#include "Monster.h"
class Bogeyman :public Monster {
public:
	Bogeyman(int x, int y);
	virtual ~Bogeyman();
	virtual void turn(Game& game);
	virtual void attackPlayer(Game& game);
private:
	void moveCloserToPlayer(Game& game);
	bool canMoveTo(int x, int y, Game& game);
};
#endif
