#include "Game.h"
#include "Bogeyman.h"
#include "Dragon.h"
#include "Goblin.h"
#include "Snakewomen.h"
#include "GameObject.h"
#include "utilities.h"
#include "Player.h"
#include "Mace.h"
#include "ShortSword.h"
#include "LongSword.h"
#include "Strength.h"
#include "Armor.h"
#include "Health.h"
#include "Dexterity.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
Game::Game(int goblinSmellDistance)
    : m_goblinSmellDistance(goblinSmellDistance), m_currentLevel(0)
{

    generateLevel(m_currentLevel); //game starts with level 0

}
Game::~Game() {
    for (size_t i = 0; i < m_monsters.size(); ++i) {
        delete m_monsters[i];
    }
    m_monsters.clear();
    for (size_t i = 0; i < m_gameObjects.size(); ++i) {
        delete m_gameObjects[i];
    }
    m_gameObjects.clear();

}
//map functions
const std::vector<std::vector<char>>& Game::getMap() const {
    return m_map;
}
void Game::generateLevel(int level) {
    clearLevel();
    initializeMap(70, 18);
    placePlayer();
    placeMonsters(level);
    placeGameObjects();
    if (level < 4) {
        placeStaircase();
    }
    else {
        placeGoldenIdol();
    }
}
void Game::clearLevel() {
    //delete monsters
    for (size_t i = 0; i < m_monsters.size(); ++i) {
        delete m_monsters[i];
    }
    m_monsters.clear();
    //delete rooms
    m_rooms.clear();
    //delete map
    m_map.clear();
    //delete objects
    for (size_t i = 0; i < m_gameObjects.size(); ++i) {
        delete m_gameObjects[i];
    }
    m_gameObjects.clear();
}
void Game::generateMaze(int width, int height) {
    std::vector<Room> rooms;
    int numRooms = randInt(3, 6);

    for (int i = 0; i < numRooms; ++i) {
        int roomWidth = randInt(8, 10);
        int roomHeight = randInt(8, 10);
        int left = randInt(1, width - roomWidth - 1);
        int top = randInt(1, height - roomHeight - 1);
        int right = left + roomWidth - 1;
        int bottom = top + roomHeight - 1;
        if (addRoom(left, top, right, bottom)) {
            rooms.push_back(Room(left, top, right, bottom));
        }
    }

    connectAllRooms(rooms);
}

bool Game::addRoom(int left, int top, int right, int bottom) {
    for (size_t i = 0; i < m_rooms.size(); ++i) {
        Room room = m_rooms[i];
        if (intersect(Room(left, top, right, bottom), room)) {
            return false;
        }
    }

    for (int y = top; y <= bottom; ++y) {
        for (int x = left; x <= right; ++x) {
            m_map[y][x] = ' ';
        }
    }

    m_rooms.push_back(Room(left, top, right, bottom));
    return true;
}

bool Game::intersect(const Room& r1, const Room& r2) const {
    // Check if two rooms intersect
    return !(r2.left > r1.right || r2.right < r1.left || r2.top > r1.bottom || r2.bottom < r1.top);
}

void Game::connectRooms(const Room& r1, const Room& r2) {
    int x1 = randInt(r1.left, r1.right);
    int y1 = randInt(r1.top, r1.bottom);
    int x2 = randInt(r2.left, r2.right);
    int y2 = randInt(r2.top, r2.bottom);

    while (x1 != x2) {
        m_map[y1][x1] = ' ';
        x1 += (x2 > x1) ? 1 : -1;
    }
    while (y1 != y2) {
        m_map[y1][x1] = ' ';
        y1 += (y2 > y1) ? 1 : -1;
    }
}

void Game::connectAllRooms(const std::vector<Room>& rooms) {
    std::vector<Room> connectedRooms; // Stores rooms that are connected
    std::vector<bool> roomConnected(rooms.size(), false); // Keeps track of connected rooms

    // Start with the first room
    connectedRooms.push_back(rooms[0]);
    roomConnected[0] = true;

    // Connect each room to at least one other room
    for (size_t i = 1; i < rooms.size(); ++i) {
        // Randomly select a connected room
        int connectedIndex = randInt(0, connectedRooms.size() - 1);
        const Room& connectedRoom = connectedRooms[connectedIndex];

        // Connect the current room to the randomly selected connected room
        connectRooms(rooms[i], connectedRoom);

        // Mark the current room as connected
        connectedRooms.push_back(rooms[i]);
        roomConnected[i] = true;
    }

    // Ensure all rooms are connected to each other
    for (size_t i = 0; i < rooms.size(); ++i) {
        if (!roomConnected[i]) {
            // If a room is not yet connected, randomly connect it to a connected room
            int connectedIndex = randInt(0, connectedRooms.size() - 1);
            const Room& connectedRoom = connectedRooms[connectedIndex];
            connectRooms(rooms[i], connectedRoom);
        }
    }
}
void Game::placeStaircase() {

    while (true) {
        int x = randInt(1, static_cast<int>(m_map[0].size() - 2));
        int y = randInt(1, static_cast<int>(m_map.size() - 2));
        if (m_map[y][x] == ' ') {
            m_map[y][x] = '>';
            break;
        }
    }

}

void Game::placeGoldenIdol() {
    while (true) {
        int x = randInt(1, static_cast<int>(m_map[0].size() - 2));
        int y = randInt(1, static_cast<int>(m_map.size() - 2));
        if (m_map[y][x] == ' ') {
            m_map[y][x] = '&'; // Use '&' to represent the golden idol
            break;
        }
    }
}
void Game::initializeMap(int width, int height) {
    m_map.resize(height, std::vector<char>(width, '#')); // Initialize with walls

    // Generate maze with rooms and corridors
    generateMaze(width, height);
}

char Game::getMapCell(int x, int y) const {
    if (isValidPosition(x, y)) {
        return m_map[y][x];
    }
    return '\0';
}

void Game::setMapCell(int x, int y, char value) {
    if (isValidPosition(x, y)) {
        m_map[y][x] = value;
    }
}

bool Game::isValidPosition(int x, int y) const {
    return (x >= 0 && x < m_map[0].size() && y >= 0 && y < m_map.size());
}
void Game::displayMap() const {
    //clearScreen();
    for (int y = 0; y < m_map.size(); ++y) {
        for (int x = 0; x < m_map[y].size(); ++x) {
            //if (isObject)continue;
            bool isMonster = false;
            for (const Monster* monster : m_monsters) {
                if (monster->getX() == x && monster->getY() == y) {
                    cout << monster->getSymbol();
                    isMonster = true;
                    break;
                }
            }
            if (isMonster)continue;
            bool isObject = false;
            for (const GameObject* gameObjects : m_gameObjects) {
                if (gameObjects->getX() == x && gameObjects->getY() == y) {
                    if (!(m_player->getX() == x && m_player->getY() == y)) {
                        cout << gameObjects->getObjectSymbol();
                        isObject = true;
                    }
                }
            }

            
            if (m_player->getX() == x && m_player->getY() == y) {
                cout << m_player->getSymbol();
            }
            else {
                if (!isObject) {
                    cout << m_map[y][x];
                }
            }
            
        }
        cout << endl;
    }
    cout << "Level: " << m_currentLevel << ", Hit points: " << this->m_player->getHitPoints() << 
    ", Armor: " << this->m_player->getArmor() << ", Strength: " << this->m_player->getStrength()
    << ", Dexterity: " << this->m_player->getDexterity() << "\n";
}
//player functions
Player* Game::getPlayer() const {
    return m_player;
}
void Game::placePlayer() {
    while (true) {
        int x = randInt(1, static_cast<int>(m_map[0].size() - 2));
        int y = randInt(1, static_cast<int>(m_map.size() - 2));

        if (m_currentLevel == 0) {
            if (m_map[y][x] == ' ') {
                m_player = new Player(x, y);
                break;
            }
        }
        else {
            if (m_map[y][x] == ' ') {
                m_player->setPosition(x, y);
                break;
            }
        }
    }
}
//monster functions
std::vector<Monster*>& Game::getMonsters(){
    return m_monsters;
}
int Game::getGoblinSmellDistance() const {
    return m_goblinSmellDistance;
}
void Game::placeMonsters(int level) {
    int numMonsters = randInt(2, 5 * (level + 1) + 1);
    for (int i = 0; i < numMonsters; ++i) {
        Monster* monster = nullptr;
        int x, y;
        do {
            x = randInt(1, static_cast<int>(m_map[0].size() - 2));
            y = randInt(1, static_cast<int>( m_map.size() - 2));
        } while (m_map[y][x] != ' ');
        //place only snakewomen and goblin for levels 0 and 1
        if (level < 2) {
            int monsterType = randInt(0, 1);
            switch (monsterType) {
                case 0: monster = new Snakewomen(x, y); break;
                case 1: monster = new Goblin(x, y); break;
            }
        }
        //place only snakewomen, goblin, and bogeyman for levels 0-2
        else if (level < 3) {
            int monsterType = randInt(0, 2);
            switch (monsterType) {
                case 0: monster = new Snakewomen(x, y); break;
                case 1: monster = new Goblin(x, y); break;
                case 2: monster = new Bogeyman(x, y); break;
            }
        }
        //starting from level 3, place all monsters
        else {
            int monsterType = randInt(0, 3);
            switch (monsterType) {
                case 0: monster = new Snakewomen(x, y); break;
                case 1: monster = new Goblin(x, y); break;
                case 2: monster = new Bogeyman(x, y); break;
                case 3: monster = new Dragon(x, y); break;
            }
            
        }

        m_monsters.push_back(monster);
    }
}
//object functions
void Game::placeGameObjects() {
    int numGameObj = randInt(2, 3);
    for (int i = 0; i < numGameObj; i++) {
        GameObject* gameObject = nullptr;
        int x, y;
        do {
            x = randInt(1, static_cast<int>(m_map[0].size() - 2));
            y = randInt(1, static_cast<int>(m_map.size() - 2));
        } while (m_map[y][x] != ' ');
        int objectType = randInt(0, 6);
        switch (objectType) {
            case 0: gameObject = new Mace(x, y); break;
            case 1: gameObject = new ShortSword(x, y); break;
            case 2: gameObject = new LongSword(x, y); break;
            case 3: gameObject = new Strength(x, y); break;
            case 4: gameObject = new Armor(x, y); break;
            case 5: gameObject = new Health(x, y); break;
            case 6: gameObject = new Dexterity(x, y); break;
        }
        m_gameObjects.push_back(gameObject);
    }

}
std::vector<GameObject*>& Game::getGameObject(){
    return m_gameObjects;
}
std::vector<std::string>& Game::getGameMessage(){
    return m_message;
}
void Game::displayGameMessage() {
    cout << endl;
    for (size_t i = 0; i < m_message.size(); ++i) {
        cout << m_message[i] << endl;
    }
}
void Game::eraseGameMessage() {
    m_message.clear();
}
void Game::play() {
    while (true) {
        clearScreen();
        displayMap();
        displayGameMessage();
        eraseGameMessage();
        //monster kills player after running their turns
        if (m_player->getHitPoints() <= 0) {
            return;
        }
        //chance of regening health if not dead
        if (randInt(1, 10) == 1 && m_player->getHitPoints()<m_player->getMaxHitPoints()) {
            if (!(m_player->getHitPoints() == m_player->getMaxHitPoints())) {
                m_player->changeHitPoints(m_player->getHitPoints()+1);
            }
        }
        char ch = getCharacter();
        Player* player = this->getPlayer();
        //quit game
        if (ch == 'q') {
            return;
        }
        //make sure player is not sleeping 
        if (m_player->getSleepTime() != 0) {
            m_player->changeSleepTime(m_player->getSleepTime() - 1);
        }
        else {
                //grab object
            if (ch == 'g') {
                if (this->getMapCell(player->getX(), player->getY()) == '&') {
                    cout << "You pick up the golden idol\nCongratulations, you won!\n";
                    cout << "Press q to exit game.";
                        
                        while (getCharacter()!='q') {

                        }
                        return;
                }
                else if (player->getInventory().size() <= 25) {
                    player->storeObject(player->getX(), player->getY(), *this);
                }
                else {
                    m_message.push_back("Your knapsack is full, you can't pick that up.");
                }
            }
            //check inventory
            else if (ch == 'i') {
                clearScreen();
                player->displayInventory();
                while (!getCharacter()) {
                }
            }
            //cheat
            else if (ch == 'c') {
                player->changeHitPoints(50);
                player->changeDexterity(9);
            }
            //wield
            else if (ch == 'w') {
                clearScreen();
                player->displayInventory();
                char c = getCharacter();
                player->wieldWeapon(c, *this);

            }
            //read scroll
            else if (ch == 'r') {
                clearScreen();
                player->displayInventory();
                char c = getCharacter();
                player->readScroll(c, *this);
            }
            //found stairs
            else if (ch == '>') {
                int x = m_player->getX();
                int y = m_player->getY();
                if (getMapCell(x, y) == '>' && m_currentLevel < 4) {
                    //deleteMap();
                    m_currentLevel++;
                    generateLevel(m_currentLevel);
                }
            }
            //move character
            else {
                switch (ch) {
                case ARROW_LEFT:  player->movePlayer(-1, 0, *this); break;
                case ARROW_RIGHT: player->movePlayer(1, 0, *this); break;
                case ARROW_UP:    player->movePlayer(0, -1, *this); break;
                case ARROW_DOWN:  player->movePlayer(0, 1, *this); break;
                }

            }
        }
        // Move monsters according to their turn logic after the player moves
        for (size_t i = 0; i < m_monsters.size(); ++i) {
            m_monsters[i]->turn(*this);

        }
    
    }
}
/*
to-do list
3. redo map implementation
4. work on goblin recursion
*/