#ifndef GOBLIN_INCLUDED
#define GOBLIN_INCLUDED

#include "Monster.h"
#include "Game.h"
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <climits>

class Goblin : public Monster {
public:
    Goblin(int x, int y);
    virtual ~Goblin();
    virtual void turn(Game& game);
    virtual void attackPlayer(Game& game);

private:
    // Returns true if the goblin can move to (x, y) (i.e., the cell is not a wall, the player, or another monster)
    bool canMoveTo(int x, int y, Game& game);

    // Given the player's position and a maximum smell distance (maxSteps),
    // this function returns the neighboring cell (as a pair) that is the best first move
    // toward the player along a traversable path (if one exists).
    std::pair<int, int> moveTowardPlayer(Game& game, int playerX, int playerY, int maxSteps);

    // Returns true if (x, y) is within the map bounds and not a wall.
    bool isValidMove(const Game& game, int x, int y);

    // Recursive function: starting from (currX, currY) with a limit of remainingSteps,
    // returns the minimum additional steps required to reach (playerX, playerY).
    // If unreachable within the limit, returns INT_MAX.
    // 'memo' caches computed best distances and 'visited' tracks the current recursion path.
    int recursiveMove(const Game& game, int currX, int currY, int playerX, int playerY,
        int remainingSteps, std::vector<std::vector<int>>& memo,
        std::vector<std::vector<bool>>& visited);
};

#endif // GOBLIN_INCLUDED
