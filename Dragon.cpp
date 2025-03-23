#include "Dragon.h"
#include "utilities.h"
Dragon::Dragon(int x, int y)
	:Monster('D', x, y, randInt(20,25), 4, 4, 4, 0, new LongSword(1,1), "Dragon")
{}
Dragon::~Dragon()
{}
void Dragon::turn(Game& game) {
	const Player* player = game.getPlayer();
	int playerX = player->getX();
	int playerY = player->getY();
	int dragonx = this->getX();
	int dragony = this->getY();
    //chance at regen before turn
    if (randInt(1, 10) == 1) {
        if (!(this->getHitPoints() == this->getMaxHitPoints())) {
            this->changeHitPoints(this->getHitPoints()+1);
        }
    }
	//check to see if you can attack player; player must be within one step away from monster
	if ((dragonx + 1 == playerX && dragony == playerY) || (dragonx - 1 == playerX && dragony == playerY) || (dragonx == playerX && dragony + 1 == playerY) || (dragonx == playerX && dragony - 1 == playerY)) {
		attackPlayer(game);
	}
}
void Dragon::attackPlayer(Game& game) {
    std::vector<std::string>& gameMessage = game.getGameMessage();
    Player* player = game.getPlayer();
    int attackPoints = this->getDexterity() + this->getWeapon()->getDexterity();
    int defenderPoints = player->getDexterity() + player->getArmor();
    //hits player
    if (randInt(1, attackPoints) >= randInt(1, defenderPoints) && player->getHitPoints() > 0) {
        int damagePoints = randInt(0, this->getStrength() + this->getWeapon()->getDamage() - 1);
        player->changeHitPoints(player->getHitPoints() - damagePoints);
        //player dead?
        if (player->getHitPoints() <= 0) {
            gameMessage.push_back("the Dragon " + player->getWeapon()->callAction() + " Player dealing a final blow.");
        }
        else {
            gameMessage.push_back("the Dragon " + player->getWeapon()->callAction() + " Player and hits.");
        }
    }
    //misses player
    else {
        if (player->getHitPoints() > 0) {
            gameMessage.push_back("the Dragon " + player->getWeapon()->callAction() + " Player and misses");
        }
    }
}