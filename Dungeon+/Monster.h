//#ifndef ENEMY_H_INCLUDED
//#define ENEMY_H_INCLUDED
#ifndef MONSTER_H_INCLUDED
#define MONSTER_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "Poison.h"
#include "GameCharacter.h"
#include "Skill.h" 

using namespace std;

class Skill;
class Poison;

class Monster: public GameCharacter
{
private:
    vector<Skill> skills;
    Poison poison;
public:
    Monster();
    Monster(string,int,int, int, int,int,int);

    /* Virtual function that you need to complete   */
    /* In Monster, this function should deal with   */
    /* the combat system.                           */
    bool triggerEvent(Object*);
    void addSkill(Skill);
    void fight(Player*, int);
    void setPoison(Poison);
    vector<Skill> getSkill();
    Poison getPoison();
};


#endif // ENEMY_H_INCLUDED
