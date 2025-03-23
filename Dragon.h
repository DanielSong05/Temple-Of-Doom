#ifndef DRAGON_INCLUDED
#define DRAGON_INCLUDED
#include "Monster.h"
class Dragon:public Monster {
public:
	Dragon(int x, int y);
	virtual ~Dragon();
	virtual void turn(Game& game);
	virtual void attackPlayer(Game& game);
};
#endif
