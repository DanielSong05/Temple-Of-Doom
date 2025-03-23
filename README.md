# Temple of Doom

**South Dakota Smith and the Temple of Doom** is an action-adventure game inspired by the adventures of an archaeology professor who once stole ancient artifacts but now redeems himself by donating game profits to the descendants of the original creators. In this game, you explore a multi-level temple, battle monsters, pick up treasures, and ultimately search for the elusive golden idol.

---

## Table of Contents

- [Overview](#overview)
- [Gameplay](#gameplay)
- [Monsters](#monsters)
- [Game Objects](#game-objects)
- [Controls](#controls)
- [Installation and Running the Game](#installation-and-running-the-game)
- [Project Structure](#project-structure)
- [Known Issues / Future Enhancements](#known-issues--future-enhancements)
- [License](#license)

---

## Overview

- **Temple Layout:** The temple consists of **5 levels** (numbered 0 to 4). Levels are generated at runtime as mazes that are **70 columns wide** and **18 rows high**. Each level features rooms connected by corridors.
- **Objective:** Start on level 0 and navigate through the temple until you reach level 4, where you must locate and pick up the **golden idol** (displayed as `&`) to win the game.
- **Dynamic Levels:** Each time you descend via a stairway (displayed as `>`), a new level is generated with random placement of the player, monsters, and objects.

---

## Gameplay

- **Exploration:**  
  Navigate through a maze-like temple while avoiding impenetrable walls (`#`) and traversing corridors.

- **Combat:**  
  Engage in battles with various monsters by moving into their space to attack.

- **Treasure and Power-Ups:**  
  Pick up weapons (e.g., maces, short swords, long swords, magic axes, magic fangs of sleep) and scrolls (e.g., scrolls of teleportation, enhance armor, raise strength, enhance health, enhance dexterity) to boost your abilities.

- **Player Stats:**  
  Manage your hit points, armor, strength, and dexterity. Use scrolls to improve these stats and wield different weapons to defeat monsters.

- **Victory/Defeat:**  
  The game is won by picking up the golden idol. It ends if your hit points drop to 0.

---

## Monsters

- **Bogeymen (B):**  
  - **Levels:** Appear only at temple level 2 or deeper.  
  - **Behavior:** Move toward the player if reachable in 1–5 steps, though their pathfinding is simple.

- **Dragons (D):**  
  - **Levels:** Appear at temple level 3 or deeper.  
  - **Behavior:** Do not move but attack if the player is adjacent. Dragons occasionally regain hit points.

- **Goblins (G):**  
  - **Levels:** May appear on any level.  
  - **Behavior:** Use a recursive algorithm to detect the player if a traversable path exists within a specified smell distance (default is 15 steps). They then make an optimal move toward the player.

- **Snakewomen (S):**  
  - **Levels:** Can appear on any level.  
  - **Behavior:** Similar to Bogeymen but with a shorter smell distance (3 steps) and different weapons (magic fangs of sleep).

---

## Game Objects

- **Walls:** Represented by `#` (impassable).
- **Stairways:** Represented by `>` (descend to the next level).
- **Golden Idol:** Represented by `&` (picking it up wins the game).
- **Weapons:** Represented by `)` and include various types like maces, short swords, long swords, magic axes, and magic fangs.
- **Scrolls:** Represented by `?` and grant effects such as teleportation, improved armor, increased strength, enhanced health, or enhanced dexterity.

---

## Controls

- **Movement:**  
  - Use **arrow keys** or **h** (left), **j** (down), **k** (up), **l** (right).
  
- **Attack:**  
  - Move into an adjacent monster’s space to attack.
  
- **Pick Up Items:**  
  - Press **g** when standing on an item.
  
- **Inventory:**  
  - Press **i** to view your inventory.
  
- **Wield Weapons:**  
  - Press **w**, then select a weapon from your inventory.
  
- **Read Scrolls:**  
  - Press **r**, then select a scroll from your inventory.
  
- **Descend Levels:**  
  - When on a stairway (`>`), press **>** to descend.
  
- **Quit:**  
  - Press **q** to quit the game.
  
- **Cheat:**  
  - Press **c** to temporarily boost player stats (used for testing).

---

## Installation and Running the Game

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/DanielSong05/Temple-Of-Doom.git
   cd Temple-Of-Doom
2. **Build the Project:**

   Use your preferred IDE (e.g., Visual Studio) or compile from the command line:

   ```bash
   g++ -o TempleOfDoom *.cpp
   ```

   *Ensure you have a C++ compiler installed (e.g., g++ on Linux/macOS or Visual Studio on Windows).*

3. **Run the Game:**

   ```bash
   ./TempleOfDoom
   ```

   *On Windows, run the generated executable (e.g., TempleOfDoom.exe).*

## Project Structure

- **Source Files:**  
  The project is organized into several `.cpp` and `.h` files, each representing different components of the game (e.g., Actor, Game, Player, Monsters, Weapons, Scrolls).

- **Build Files:**  
  Contains Visual Studio project files and build artifacts. These are excluded from version control via the `.gitignore` file.

- **Utilities:**  
  Includes helper functions such as `randInt`, `getCharacter`, and `clearScreen` for handling game input and output.

## Known Issues / Future Enhancements

- **Goblin Pathfinding:**  
  The recursive algorithm for goblin movement meets project requirements but might require further optimization if performance issues are encountered at higher smell distances.

- **Additional Monsters and Items:**  
  Future enhancements could include more varied monster behaviors and additional game objects or power-ups.

- **User Interface Improvements:**  
  Enhancements such as better map rendering, more detailed statistics, and improved controls could enhance the overall gameplay experience.

## License

*This game was developed for educational purposes and is provided as-is without any warranty.*
```

