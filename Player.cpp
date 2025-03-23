#include "Player.h"
#include "ShortSword.h"
#include "LongSword.h"
#include "MagicAxe.h"
#include "Mace.h"
#include "MagicFangs.h"
#include "Strength.h"
#include "Dexterity.h"
#include "Armor.h"
#include "Health.h"
#include "Teleportation.h"
#include <iostream>
Player::Player()
	:Actor('@', 1, 1, 20, 20,2, 2, 2, 0, new ShortSword(1,1))
{
    m_inventory.push_back(new ShortSword());
}
Player::Player(int x, int y)
	:Actor('@', x, y, 20, 20, 2, 2, 2, 0, new ShortSword(1, 1))
{
    m_inventory.push_back(new ShortSword());
}
Player::~Player() {
    for (size_t i = 0; i < m_inventory.size(); ++i) {
        delete m_inventory[i];
    }
    m_inventory.clear();
}
void Player::movePlayer(int dx, int dy, Game& game) {
    int newX = game.getPlayer()->getX() + dx;
    int newY = game.getPlayer()->getY() + dy;
    if (canMoveTo(newX, newY, game)) {
        this->setPosition(newX, newY);
    }
    
}
bool Player::canMoveTo(int x, int y, Game& game) {
    std::vector<std::string>& gameMessage = game.getGameMessage();
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
            attackMonster(*monsters[i], game);
            return false;
        }
    }

    return true;
}
void Player::attackMonster(Monster& monster, Game& game) {
    std::vector<std::string>& gameMessage = game.getGameMessage();
    std::vector<GameObject*>& gameObject = game.getGameObject();
    std::vector<Monster*>& monsters = game.getMonsters();
    Player* player = game.getPlayer();
    int attackPoints = player->getDexterity() + player->getWeapon()->getDexterity();
    int defenderPoints = monster.getDexterity() + monster.getArmor();
    bool putToSleep = false;
    //attack monster
    if (randInt(1,attackPoints)>=randInt(1,defenderPoints)) {
        int damagePoints = randInt(0, player->getStrength() + player->getWeapon()->getDamage() - 1);
        monster.changeHitPoints(monster.getHitPoints() - damagePoints);
        //check for magicFang
        //std::string action = player->getWeapon()->callAction();
        if (player->getWeapon()->getName() == "magic fangs") {
            //sleep
            if (randInt(1,5)==1) {
                putToSleep = true;
                int sleep = randInt(2, 6);
                //check to see if monster is already sleeping
                if (monster.getSleepTime() > 0) {
                    if (sleep > monster.getSleepTime()) monster.changeSleepTime(sleep);
                }
                else {
                    monster.changeSleepTime(sleep);
                }
            }
        }
        //drop weapon if monster is dead
        if (monster.getHitPoints() <= 0) {
            //Bogeyman
            if (monster.getSymbol() == 'B') {
                int dropChance = randInt(1,10);
                //makes sure the map is empty
                if (dropChance == 1 && game.getMapCell(monster.getX(), monster.getY())==' ') {
                    bool notOnWeapon = true;
                    //makes sure there is no weapon on the cell either; we don't need to worry about other monsters on the cell because our other codes take care of that
                    for (size_t i = 0; i < gameObject.size(); ++i) {
                        if (gameObject[i]->getX() == monster.getX() && gameObject[i]->getY() == monster.getY()) {
                            notOnWeapon = false;
                            break;
                       }
                    }
                    if (notOnWeapon) {
                        Weapon* weapon = new MagicAxe(monster.getX(), monster.getY());
                        gameObject.push_back(weapon);
                    }
                }
            }
            //SnakeWomen
            else if (monster.getSymbol() == 'S') {
                int dropChance = randInt(1, 3);
                //makes sure the map is empty
                if (dropChance == 1 && game.getMapCell(monster.getX(), monster.getY()) == ' ') {
                    bool notOnWeapon = true;
                    //makes sure there is no weapon on the cell either; we don't need to worry about other monsters on the cell because our other codes take care of that
                    for (size_t i = 0; i < gameObject.size(); ++i) {
                        if (gameObject[i]->getX() == monster.getX() && gameObject[i]->getY() == monster.getY()) {
                            notOnWeapon = false;
                            break;
                        }
                    }
                    if (notOnWeapon) {
                        Weapon* weapon = new MagicFangs(monster.getX(), monster.getY());
                        gameObject.push_back(weapon);
                    }
                }
            }
            //Goblin
            else if (monster.getSymbol() == 'G') {
                int dropChance = randInt(1, 3);
                //makes sure the map is empty
                if (dropChance == 1 && game.getMapCell(monster.getX(), monster.getY()) == ' ') {
                    bool notOnWeapon = true;
                    //makes sure there is no weapon on the cell either; we don't need to worry about other monsters on the cell because our other codes take care of that
                    for (size_t i = 0; i < gameObject.size(); ++i) {
                        if (gameObject[i]->getX() == monster.getX() && gameObject[i]->getY() == monster.getY()) {
                            notOnWeapon = false;
                            break;
                        }
                    }
                    if (notOnWeapon) {
                        Weapon* weapon = nullptr;
                        int weaponType = randInt(1, 2);
                        switch (weaponType) {
                        case 1: weapon = new MagicFangs(monster.getX(), monster.getY()); break;
                        case 2: weapon = new MagicAxe(monster.getX(), monster.getY()); break; 
                        }
                        gameObject.push_back(weapon);
                    }
                }
            }
            //Dragons
            else if (monster.getSymbol() == 'D') {
                //makes sure the map is empty
                if (game.getMapCell(monster.getX(), monster.getY()) == ' ') {
                    bool notOnWeapon = true;
                    //makes sure there is no weapon on the cell either; we don't need to worry about other monsters on the cell because our other codes take care of that
                    for (size_t i = 0; i < gameObject.size(); ++i) {
                        if (gameObject[i]->getX() == monster.getX() && gameObject[i]->getY() == monster.getY()) {
                            notOnWeapon = false;
                            break;
                        }
                    }
                    if (notOnWeapon) {
                        //drop a random scroll
                        int scrollType = randInt(0, 4);
                        Scroll* scroll = nullptr;
                        switch (scrollType) {
                        case 0: scroll = new Teleportation(monster.getX(), monster.getY()); break;
                        case 1: scroll = new Strength(monster.getX(), monster.getY()); break;
                        case 2: scroll = new Dexterity(monster.getX(), monster.getY()); break;
                        case 3: scroll = new Armor(monster.getX(), monster.getY()); break;
                        case 4: scroll = new Health(monster.getX(), monster.getY()); break;
                        }
                        gameObject.push_back(scroll);
                    }
                }
            }
            for (size_t i = 0; i < monsters.size(); ++i) {
                if (monsters[i]->getX() == monster.getX() && monsters[i]->getY() == monster.getY()) {
                    monsters.erase(monsters.begin() + i);
                    break;
                }
            }
            gameMessage.push_back("Player " + player->getWeapon()->callAction() + " the " + monster.getName() + " dealing a final blow.");
        }
        else {
            if (putToSleep) {
                gameMessage.push_back("Player " + player->getWeapon()->callAction() + " the " + monster.getName() + " and hits, putting " + monster.getName() + " to sleep.");
            }
            else {
                gameMessage.push_back("Player " + player->getWeapon()->callAction() + " the " + monster.getName() + " and hits.");
            }
        }
       
    }
    else {
        gameMessage.push_back("Player " + player->getWeapon()->callAction() + " the " + monster.getName() + " and misses.");
    }

}
void Player::storeObject(int x, int y, Game& game) {
    std::vector<GameObject*>& gameObject = game.getGameObject();
    std::vector<std::string>& gameMessage = game.getGameMessage();
    for (size_t i = 0; i < gameObject.size(); ++i) {
        if (gameObject[i]->getX() == x && gameObject[i]->getY() == y) {
            m_inventory.push_back(gameObject[i]);
            if (gameObject[i]->getObjectSymbol() == ')') {
                std::string n = "You pick up " + gameObject[i]->getName();
                gameMessage.push_back(n);
            }
            else if (gameObject[i]->getObjectSymbol() == '?') {
                std::string n = "You pick up a scroll called " + gameObject[i]->getName();
                gameMessage.push_back(n);
            }
            gameObject.erase(gameObject.begin()+i);
            break;
        }
    }
}
const std::vector<GameObject*>& Player::getInventory() const {
    return m_inventory;
}
void Player::displayInventory() {
    char a[] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m'
                ,'n','o','p','q','r','s','t','u','v','w','x','y','z' };
    std::cout << "Inventory: \n";
    for (size_t i = 0; i < m_inventory.size(); ++i) {
        if (m_inventory[i]->getObjectSymbol()=='?') {
            std::cout << " " << a[i] << ". A scroll called " << m_inventory[i]->getName() << std::endl;
        }
        else {
            std::cout << " " << a[i] << ". " << m_inventory[i]->getName() << std::endl;
        }
    }
}
void Player::wieldWeapon(char c, Game& game) {
    std::vector<std::string>& gameMessage = game.getGameMessage();
    char a[] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m'
                ,'n','o','p','q','r','s','t','u','v','w','x','y','z' };
    for (int i = 0; i < m_inventory.size(); i++) {
        //if there is an object in that index of the inventory
        if (c == a[i]) {
            Weapon* weapon = dynamic_cast<Weapon*>(m_inventory[i]);
            if (weapon) {
                game.getPlayer()->changeWeapon(weapon);
                gameMessage.push_back("You are wielding " + weapon->getName());
            }
            else {
                gameMessage.push_back("You can't wield " + m_inventory[i]->getName());
            }
        }
    }
}
void Player::readScroll(char c, Game& game) {
    std::vector<std::string>& gameMessage = game.getGameMessage();
    char a[] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m'
                ,'n','o','p','q','r','s','t','u','v','w','x','y','z' };
    for (int i = 0; i < m_inventory.size(); i++) {
        //if there is an object in that index of the inventory
        if (c == a[i]) {
            //if that index is a scroll
            if (m_inventory[i]->getObjectSymbol() == '?') {
                //check for the type of scroll
                //dexterity
                if (m_inventory[i]->callAction() == "You feel like less of a klutz.") {
                    int curDex = game.getPlayer()->getDexterity()+1;
                    if (curDex > 99) curDex = 99;
                    game.getPlayer()->changeDexterity(curDex);
                    gameMessage.push_back(m_inventory[i]->callAction());
                    
                }
                //health
                else if (m_inventory[i]->callAction() == "You feel your heart beating stronger.") {
                    int curMaxHP = game.getPlayer()->getMaxHitPoints() + randInt(3,8);
                    if (curMaxHP > 99) curMaxHP = 99;
                    game.getPlayer()->changeMaxHitPoints(curMaxHP);
                    gameMessage.push_back(m_inventory[i]->callAction());
                    
                }
                //strength
                else if (m_inventory[i]->callAction() == "Your muscles bulge.") {
                    int curStrength = game.getPlayer()->getStrength() + randInt(1,3);
                    if (curStrength > 99) curStrength = 99;
                    game.getPlayer()->changeStrength(curStrength);
                    gameMessage.push_back(m_inventory[i]->callAction());
                    
                }
                //armor
                else if (m_inventory[i]->callAction() == "Your armor glows blue.") {
                    int curArmor = game.getPlayer()->getArmor() + randInt(1,3);
                    if (curArmor > 99) curArmor = 99;
                    game.getPlayer()->changeArmor(curArmor);
                    gameMessage.push_back(m_inventory[i]->callAction());
                    
                }
                //teleporation
                else if (m_inventory[i]->callAction() == "You feel your body wrenched in space and time.") {
                    while (true) {

                        int x = randInt(1, 68);
                        int y = randInt(1, 16);

                        if (game.getMapCell(x, y)==' ') {
                            game.getPlayer()->changeX(x);
                            game.getPlayer()->changeY(y);
                            break;
                        }
                    }
                    gameMessage.push_back(m_inventory[i]->callAction());
                    
                }
                //make sure to delete the scroll from inventory
                delete m_inventory[i];
                m_inventory.erase(m_inventory.begin() + i);
                //adjusting loop since we are erasing an item
                i--;
                break;
            }
            if (m_inventory[i]->getObjectSymbol() == ')') {
                gameMessage.push_back("You can't read the scroll called " + m_inventory[i]->getName());
            }
        }
    }
}