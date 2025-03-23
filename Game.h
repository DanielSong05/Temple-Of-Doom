// Game.h
#ifndef GAME_INCLUDED
#define GAME_INCLUDED
#include <string>
#include <vector>
class Player;
class Monster;
class GameObject;
struct Room {
    int left, top, right, bottom;
    Room(int l, int t, int r, int b) : left(l), top(t), right(r), bottom(b) {}
};
class Game {
public:
    Game(int goblinSmellDistance);
    ~Game();
    void play();
    
    //creating map
    void initializeMap(int width, int height);
    const std::vector<std::vector<char>>& getMap() const;
    char getMapCell(int x, int y) const;
    void setMapCell(int x, int y, char value);
    bool isValidPosition(int x, int y) const;
    int getGoblinSmellDistance() const;
    void generateMaze(int width, int height);
    bool addRoom(int left, int top, int right, int bottom);
    bool intersect(const Room& r1, const Room& r2) const;
    void connectRooms(const Room& r1, const Room& r2);
    void connectAllRooms(const std::vector<Room>& rooms);
    void displayMap()const;
    void generateLevel(int level);
    void clearLevel();
    void placeStaircase();
    void placeGoldenIdol();

    //player related functions
    Player* getPlayer() const;
    void placePlayer();
    //void movePlayer(int dx, int dy);

    //monster related functions
    void placeMonsters(int level);
    std::vector<Monster*>& getMonsters();

    //object related functions
    void placeGameObjects();
    std::vector<GameObject*>& getGameObject();

    std::vector<std::string>& getGameMessage();
    void displayGameMessage();
    void eraseGameMessage();
private:
    int m_goblinSmellDistance;
    int m_currentLevel;
    std::vector<std::vector<char> > m_map;
    std::vector<Room> m_rooms;
    std::vector<GameObject*> m_gameObjects;
    std::vector<Monster*> m_monsters;
    std::vector<std::string> m_message;
    Player* m_player;


};

#endif // GAME_INCLUDED