#include "Bogeyman.h"
Bogeyman::Bogeyman(int x, int y)
	:Monster('B', x, y, randInt(5,10), 2, randInt(2,3), randInt(2,3), 0, new ShortSword(1,1), "Bogeyman")
{}
Bogeyman::~Bogeyman()
{}

void Bogeyman::turn(Game& game) {
    const Player* player = game.getPlayer();
	int playerX = player->getX();
	int playerY = player->getY();
	int bogeyx = this->getX();
	int bogeyy = this->getY();
	int distance = abs(playerX - bogeyx) + abs(playerY - bogeyy);
    //check to see if you can attack player; player must be within one step away from monster
    if ((bogeyx+1 == playerX && bogeyy == playerY) || (bogeyx-1 == playerX && bogeyy == playerY) || (bogeyx == playerX && bogeyy+1 == playerY) || (bogeyx == playerX && bogeyy-1 == playerY)){
        attackPlayer(game);
    }
    //check to see if you can move towards the player
	else if (distance <= 5) {
		moveCloserToPlayer(game);
	}
}
void Bogeyman::attackPlayer(Game& game) {
    std::vector<std::string>& gameMessage = game.getGameMessage();
    Player* player = game.getPlayer();
    int attackPoints = this->getDexterity() + this->getWeapon()->getDexterity();
    int defenderPoints = player->getDexterity() + player->getArmor();
    //hits player
    if (randInt(1, attackPoints) >= randInt(1, defenderPoints) && player->getHitPoints()>0) {
        int damagePoints = randInt(0, this->getStrength() + this->getWeapon()->getDamage() - 1);
        player->changeHitPoints(player->getHitPoints() - damagePoints);
        //player dead?
        if (player->getHitPoints() <= 0) {
            gameMessage.push_back("the Bogeyman " + player->getWeapon()->callAction() + " Player dealing a final blow.");
        }
        else {
           gameMessage.push_back("the Bogeyman " + player->getWeapon()->callAction() + " Player and hits."); 
        }
    }
    //misses player
    else {
        if (player->getHitPoints() > 0) {
            gameMessage.push_back("the Bogeyman " + player->getWeapon()->callAction() + " Player and misses");
        }
    }
}
bool Bogeyman::canMoveTo(int x, int y, Game& game) {
    const Player* player = game.getPlayer();
    if (game.getMapCell(x, y) == '#') {
        return false;
    }
    if (player->getX() == x && player->getY() == y) {
        return false;
    }

    const std::vector<Monster*>& monsters = game.getMonsters();
    for (size_t i = 0; i < monsters.size(); ++i) {
        if (monsters[i]->getX() == x && monsters[i]->getY() == y) {
            return false;
        }
    }
    
    return true;
}
void Bogeyman::moveCloserToPlayer(Game& game) {
    const Player* player = game.getPlayer();
    int playerX = player->getX();
    int playerY = player->getY();
    int bogeyX = this->getX();
    int bogeyY = this->getY();

    int deltaX = playerX - bogeyX;
    int deltaY = playerY - bogeyY;
    
    //try vertical
    if (deltaX > 0 && canMoveTo(bogeyX + 1, bogeyY, game)) {
        this->setPosition(bogeyX + 1, bogeyY);
    }
    else if (deltaX < 0 && canMoveTo(bogeyX - 1, bogeyY, game)) {
        this->setPosition(bogeyX - 1, bogeyY);
    }
    // Try vertical movement if horizontal is blocked
    else if (deltaY > 0 && canMoveTo(bogeyX, bogeyY + 1, game)) {
        this->setPosition(bogeyX, bogeyY + 1);
    }
    else if (deltaY < 0 && canMoveTo(bogeyX, bogeyY - 1, game)) {
        this->setPosition(bogeyX, bogeyY - 1);
    }
}