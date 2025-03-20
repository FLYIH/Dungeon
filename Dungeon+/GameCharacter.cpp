#include "GameCharacter.h"

/* Constructor */
GameCharacter::GameCharacter() {
    // Initialize member variables to default values
    /*name = "";
    maxHealth = 0;
    currentHealth = 0;
    attack = 0;
    defense = 0;*/
}

GameCharacter::GameCharacter(string newName, string newTag, int newMaxHealth,int newHealth, int newMaxMagic, int newMagic, int newAttack, int newDefense, int newHunger, int newThirst)
    : Object(newName, newTag), name(newName), maxHealth(newMaxHealth), currentHealth(newHealth),
      maxMagic(newMaxMagic), currentMagic(newMagic), attack(newAttack), defense(newDefense),
      maxHunger(50), currentHunger(newHunger), maxThirst(50), currentThirst(newThirst) {}


/* Getter and setter functions */
void GameCharacter::setMaxHealth(int newmaxhealth) {
    maxHealth = newmaxhealth;
}

void GameCharacter::setCurrentHealth(int newCurrentHealth) {
    if(newCurrentHealth > 120) {
        currentHealth = 120;
    } else if(newCurrentHealth <= 0) {
        // the would end the game
        currentHealth = 0;
    } else {
        currentHealth = newCurrentHealth;
    }
}

void GameCharacter::setMaxMagic(int newmaxmagic) {
    maxMagic = newmaxmagic;
}

void GameCharacter::setCurrentMagic(int newCurrentMagic) {
    if(newCurrentMagic > 120) {
        currentMagic = 120;
    } else if(newCurrentMagic <= 0) {
        // the would end the game
        currentMagic = 0;
    } else {
        currentMagic = newCurrentMagic;
    }
}
void GameCharacter::setAttack(int newAttack) {
    if(newAttack > 99) attack = 99;
    else if(newAttack < 0) attack = 0;
    else attack = newAttack;
}

void GameCharacter::setDefense(int newDefense) {
    if(newDefense > 99) defense = 99;
    else if(newDefense < 0) defense = 0;
    else defense = newDefense;
}

void GameCharacter::setCurrentHunger(int newCurrentHunger) {
    if(newCurrentHunger > 50) {
        // may end the game
        setCurrentHealth(getCurrentHealth() - newCurrentHunger + 50);
        currentHunger = 50;
    } else if(newCurrentHunger < 0){
        currentHunger = 0;
    } else {
        currentHunger = newCurrentHunger;
    }
}

void GameCharacter::setCurrentThirst(int newCurrentThirst) {
    if(newCurrentThirst > 50) {
        // may end the game
        setCurrentHealth(getCurrentHealth() - newCurrentThirst + 50);
        setAttack(getAttack() - 2);
        currentThirst = 50;
    } else if(newCurrentThirst < 0) {
        currentThirst = 0;
    } else {
        currentThirst = newCurrentThirst;
    }
}

int GameCharacter::getMaxHealth() {
    return maxHealth;
}

int GameCharacter::getCurrentHealth() {
    return currentHealth;
}

int GameCharacter::getMaxMagic() {
    return maxMagic;
}

int GameCharacter::getCurrentMagic() {
    return currentMagic;
}

int GameCharacter::getAttack() {
    return attack;
}

int GameCharacter::getDefense() {
    return defense;
}

int GameCharacter::getCurrentHunger() {
    return currentHunger;
}

int GameCharacter::getCurrentThirst() {
    return currentThirst;
}
int GameCharacter::getMaxHunger() {
    return maxHunger;
}

int GameCharacter::getMaxThirst() {
    return maxThirst;
}

