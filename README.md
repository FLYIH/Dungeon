# Dungeon

## Game Overview

Dungeon RPG is a text-based adventure game developed in C++ using object-oriented programming. Players will explore various rooms in a dungeon, trade with NPCs, battle monsters, and find key items to unlock victory conditions. The game features a turn-based combat system, hunger and thirst mechanics, multiple rooms, and random events.
## [Game Demo](https://youtu.be/OtjqpSCZ_hk)

## Compilation and Execution

To compile the game, use the following command:

```
cd Dungeon_file
g++ -std=c++11 -Wall *.cpp -o dungeon
```
Then, run the game with:
```
./dungeon
```

## Gameplay

### Character Attributes

- HP (Health): Life points; the game ends if it drops to 0.

- MP (Magic): Magic points; used for casting skills.

- Hunger: Indicates hunger level; if too high, it affects health.

- Thirst: Indicates thirst level; if too high, it affects attack power and health.

### Main Systems

#### 1. Action Menu

- Move to different rooms.

- Display the player's current status.

- Open the backpack and use items.

- Trade items and recover health.

- Exit the game.
#### 2. Movement System

- Players choose a direction to move; invalid directions are hidden.

- Entering a room may trigger random events.
#### 3. Status Display

- Shows the player's current attributes.

- Displays both player and monster stats during combat.

#### 4. Item System

- Items are categorized as consumable or permanent.

- Some items can be used during battles.
#### 5. NPC Trading System

- Players can trade with NPCs to acquire useful items.

- If the player lacks enough coins, they cannot make a purchase.

#### 6. Fighting System

- Turn-based combat.

- Players use skills, consuming MP accordingly.

- Players can flee; if successful, the monster retains its previous state.

#### 7. Game Logic - Win/Loss Conditions

- Find the secret room's password, obtain Milk, and exit the dungeon to win.

- If HP drops to 0, the player loses.
### Special Mechanics
- Hunger & Thirst System

  - Moving increases hunger and thirst levels, which affect player stats if too high.

  - Can be alleviated by consuming food and drinks.

- Poison System

  - Players may become poisoned due to monster attacks or wrong choices.

  - Poison can be cured using Milk or Antidote.
### Room System
- The game consists of various rooms, each with unique functionalities:

- Desert: May encounter sandstorms or find an oasis.

- Forest: Encounter monsters or capture animals for trading.

- Swamp: Players must react quickly to escape; failure results in combat.

- Hotel: Provides a map.

- Cave: Players fight a monster; winning grants a weapon.

- Secret Room: Requires a password; contains Milk, necessary for victory.
## Code Structure
- Dungeon.cpp: Manages the main game loop and logic.

- GameCharacter.h / .cpp: Defines character attributes.

- Player.h / .cpp: Handles player actions and status updates.

- Monster.h / .cpp: Manages monster behavior and combat logic.

- NPC.h / .cpp: Defines NPC trading and interactions.

- Item.h / .cpp: Manages item types and usage.

- Room.h / .cpp: Handles room-based events.
