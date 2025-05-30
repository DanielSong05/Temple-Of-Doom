#include "Snakewomen.h"
#include "utilities.h"
Snakewomen::Snakewomen(int x, int y)
	:Monster('S', x, y, randInt(3,6), 3, 2, 3, 0, new MagicFangs(1,1), "Snakewomen")
{}
Snakewomen::~Snakewomen()
{}
void Snakewomen::turn(Game& game) {
    const Player* player = game.getPlayer();
	int playerX = player->getX();
	int playerY = player->getY();
	int snakex = this->getX();
	int snakey = this->getY();
	int distance = abs(playerX - snakex) + abs(playerY - snakey);
    //check to see if you can attack player; player must be within one step away from monster
    if ((snakex + 1 == playerX && snakey == playerY) || (snakex - 1 == playerX && snakey == playerY) || (snakex == playerX && snakey + 1 == playerY) || (snakex == playerX && snakey - 1 == playerY)) {
        attackPlayer(game);
    }
    //check to see if you can move towards the player
    else if (distance <= 5) {
        moveCloserToPlayer(game);
    }
}
void Snakewomen::attackPlayer(Game& game) {
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
            gameMessage.push_back("the Snakewomen " + player->getWeapon()->callAction() + " Player dealing a final blow.");
        }
        else {
            gameMessage.push_back("the Snakewomen " + player->getWeapon()->callAction() + " Player and hits.");
        }
    }
    //misses player
    else {
        if (player->getHitPoints() > 0) {
            gameMessage.push_back("the Snakewomen " + player->getWeapon()->callAction() + " Player and misses");
        }
    }
}
bool Snakewomen::canMoveTo(int x, int y, Game& game) {
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
void Snakewomen::moveCloserToPlayer(Game& game) {
    const Player* player = game.getPlayer();
    int playerX = player->getX();
    int playerY = player->getY();
    int snakeX = this->getX();
    int snakeY = this->getY();

    int deltaX = playerX - snakeX;
    int deltaY = playerY - snakeY;

    //try vertical
    if (deltaX > 0 && canMoveTo(snakeX + 1, snakeY, game)) {
        this->setPosition(snakeX + 1, snakeY);
    }
    else if (deltaX < 0 && canMoveTo(snakeX - 1, snakeY, game)) {
        this->setPosition(snakeX - 1, snakeY);
    }
    // Try vertical movement if horizontal is blocked
    else if (deltaY > 0 && canMoveTo(snakeX, snakeY + 1, game)) {
        this->setPosition(snakeX, snakeY + 1);
    }
    else if (deltaY < 0 && canMoveTo(snakeX, snakeY - 1, game)) {
        this->setPosition(snakeX, snakeY - 1);
    }
}