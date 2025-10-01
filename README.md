# Tiny Text RPG (C++)

A simple text-based RPG game written in **C++**. This game features character creation, combat, inventory, leveling, and a save/load system. It is designed to be easy to understand, extend, and modify.

---

## Features

* **Character Creation**

  * Choose your name and class (Warrior, Mage, Rogue).
* **Leveling System**

  * Gain XP from battles and increase your stats.
* **Turn-Based Combat**

  * Options: Attack, Defend, Use Potion, or Flee.
* **Inventory System**

  * Potions to heal during and outside combat.
* **Shop**

  * Buy healing items using gold earned in battles.
* **Save / Load**

  * Game state is saved to `savegame.txt`.
* **Random Encounters**

  * Fight different enemies like Goblins, Wolves, and Bandits.

---

## Requirements

* C++17 or later
* Any standard C++ compiler (g++, clang++, MSVC)

---

## Compilation

Using **g++**:

```bash
g++ -std=c++17 text_rpg.cpp -o text_rpg
```

---

## Running the Game

```bash
./text_rpg
```

On Windows:

```bash
text_rpg.exe
```

---

## How to Play

1. Start a **New Game** or **Load Game**.
2. Create your character (name + class).
3. Use the **Town Menu**:

   * `1` Go on Adventure (fight enemies)
   * `2` Rest (restore HP for 10 gold)
   * `3` Inventory (view/use items)
   * `4` Shop (buy potions)
   * `5` Save Game
   * `6` Exit
4. During combat:

   * `1` Attack
   * `2` Defend (reduces damage)
   * `3` Use Potion (if available)
   * `4` Flee (chance-based)

---

## Save System

* Game saves to `savegame.txt` in the same directory.
* Includes character stats, gold, and inventory.

---

## Example Gameplay

```
*** Welcome to Tiny Text RPG ***
1) New Game
2) Load Game
Choose: 1
Enter your name: Virender
Choose class: 1) Warrior 2) Mage 3) Rogue
> 1

Welcome, Virender the Warrior!

=== Town Menu ===
1) Go on Adventure (fight)
2) Rest (restore HP for 10 gold)
3) Inventory
4) Shop
5) Save Game
6) Exit
Choose: 1

You encounter a Goblin!
Enemy: Goblin  HP:14
-- Virender the Warrior --
Level: 1   XP: 0/10
HP: 30/30   ATK: 6   DEF: 2
Gold: 20
```

---

## Future Improvements

* Add equipment (weapons, armor, stat modifiers)
* Add quests or a storyline
* Introduce more enemy types and bosses
* Add multiple towns and locations
* Improve save file format (JSON, XML)

---

## License

This project is free to use, modify, and distribute for learning and personal projects.
