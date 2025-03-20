#ifndef GAMECHARACTER_H_INCLUDED
#define GAMECHARACTER_H_INCLUDED

#include <iostream>
#include <string>
#include "Object.h"
using namespace std;

class GameCharacter: public Object
{
private:
    string name;
    int maxHealth;
    int currentHealth;
    int maxMagic;
    int currentMagic;
    int attack;
    int defense;
    int maxHunger;
    int currentHunger;
    int maxThirst;
    int currentThirst;
public:
    GameCharacter();
    GameCharacter(string,string,int, int, int, int,int,int,int,int);
    bool checkIsDead();
    int takeDamage(int);

    /* Set & Get function*/
    void setMaxHealth(int);
    void setCurrentHealth(int);
    void setMaxMagic(int);
    void setCurrentMagic(int);
    void setAttack(int);
    void setDefense(int);
    void setCurrentHunger(int);
    void setCurrentThirst(int);

    int getMaxHealth();
    int getCurrentHealth();
    int getMaxMagic();
    int getCurrentMagic();
    int getAttack();
    int getDefense();
    int getCurrentHunger();
    int getCurrentThirst();
    int getMaxHunger();
    int getMaxThirst();
};
#endif // GAMECHARACTER_H_INCLUDED
