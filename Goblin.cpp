#include "Goblin.h"
#include "Game.h"
#include "Player.h"
#include <vector>
#include <climits>
#include <utility>
#include "utilities.h"

Goblin::Goblin(int x, int y)
    : Monster('G', x, y, randInt(15, 20), 1, 3, 1, 0, new ShortSword(1, 1), "Goblin")
{}

Goblin::~Goblin() {}

void Goblin::turn(Game& game) {
    const Player* player = game.getPlayer();
    int playerX = player->getX();
    int playerY = player->getY();
    int goblinX = this->getX();
    int goblinY = this->getY();

    // If the goblin is adjacent to the player, attack.
    if ((goblinX + 1 == playerX && goblinY == playerY) ||
        (goblinX - 1 == playerX && goblinY == playerY) ||
        (goblinX == playerX && goblinY + 1 == playerY) ||
        (goblinX == playerX && goblinY - 1 == playerY)) {
        attackPlayer(game);
    }
    else {
        // Otherwise, determine the best move using the recursive search.
        std::pair<int, int> newPosition = moveTowardPlayer(game, playerX, playerY, game.getGoblinSmellDistance());
        if (canMoveTo(newPosition.first, newPosition.second, game))
            this->setPosition(newPosition.first, newPosition.second);
    }
}

int Goblin::recursiveMove(const Game& game, int currX, int currY, int playerX, int playerY,
    int remainingSteps, std::vector<std::vector<int>>& memo,
    std::vector<std::vector<bool>>& visited) {
    int height = game.getMap().size();
    int width = game.getMap()[0].size();

    // Out-of-bounds check.
    if (currX < 0 || currX >= width || currY < 0 || currY >= height)
        return INT_MAX;

    // If this cell is a wall, return INT_MAX.
    if (game.getMapCell(currX, currY) == '#')
        return INT_MAX;

    // If the player's cell is reached, return 0 additional steps.
    if (currX == playerX && currY == playerY)
        return 0;

    // If no remaining steps, path is not reachable.
    if (remainingSteps <= 0)
        return INT_MAX;

    // Avoid cycles by checking if this cell is already on the current recursion path.
    if (visited[currY][currX])
        return INT_MAX;

    // If we have already computed the best result from this cell, return it.
    if (memo[currY][currX] != -1)
        return memo[currY][currX];

    // Mark the cell as visited.
    visited[currY][currX] = true;
    int best = INT_MAX;
    std::vector<std::pair<int, int>> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
    for (auto d : directions) {
        int nextX = currX + d.first;
        int nextY = currY + d.second;
        int result = recursiveMove(game, nextX, nextY, playerX, playerY, remainingSteps - 1, memo, visited);
        if (result != INT_MAX && 1 + result < best)
            best = 1 + result;
    }
    // Backtrack: unmark the cell.
    visited[currY][currX] = false;
    memo[currY][currX] = best;
    return best;
}

std::pair<int, int> Goblin::moveTowardPlayer(Game& game, int playerX, int playerY, int maxSteps) {
    int startX = this->getX();
    int startY = this->getY();

    int height = game.getMap().size();
    int width = game.getMap()[0].size();

    std::pair<int, int> bestMove = { startX, startY };
    int bestDistance = INT_MAX;
    std::vector<std::pair<int, int>> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

    // Evaluate each neighboring cell.
    for (auto d : directions) {
        int newX = startX + d.first;
        int newY = startY + d.second;
        if (!canMoveTo(newX, newY, game))
            continue;

        // Initialize fresh memo and visited tables.
        std::vector<std::vector<int>> memo(height, std::vector<int>(width, -1));
        std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));
        int dist = recursiveMove(game, newX, newY, playerX, playerY, maxSteps, memo, visited);
        if (dist < bestDistance) {
            bestDistance = dist;
            bestMove = { newX, newY };
        }
    }
    return bestMove;
}

bool Goblin::isValidMove(const Game& game, int x, int y) {
    int height = game.getMap().size();
    int width = game.getMap()[0].size();
    return (x >= 0 && x < width && y >= 0 && y < height && game.getMapCell(x, y) != '#');
}

bool Goblin::canMoveTo(int x, int y, Game& game) {
    const Player* player = game.getPlayer();
    if (game.getMapCell(x, y) == '#')
        return false;
    if (player->getX() == x && player->getY() == y)
        return false;
    const std::vector<Monster*>& monsters = game.getMonsters();
    for (auto monster : monsters) {
        if (monster->getX() == x && monster->getY() == y)
            return false;
    }
    return true;
}

void Goblin::attackPlayer(Game& game) {
    std::vector<std::string>& gameMessage = game.getGameMessage();
    Player* player = game.getPlayer();
    int attackPoints = this->getDexterity() + this->getWeapon()->getDexterity();
    int defenderPoints = player->getDexterity() + player->getArmor();

    if (randInt(1, attackPoints) >= randInt(1, defenderPoints) && player->getHitPoints() > 0) {
        int damagePoints = randInt(0, this->getStrength() + this->getWeapon()->getDamage() - 1);
        player->changeHitPoints(player->getHitPoints() - damagePoints);
        if (player->getHitPoints() <= 0)
            gameMessage.push_back("the Goblin " + player->getWeapon()->callAction() + " Player dealing a final blow.");
        else
            gameMessage.push_back("the Goblin " + player->getWeapon()->callAction() + " Player and hits.");
    }
    else {
        if (player->getHitPoints() > 0)
            gameMessage.push_back("the Goblin " + player->getWeapon()->callAction() + " Player and misses.");
    }
}
