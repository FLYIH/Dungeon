#ifndef SKILL_H_INCLUDED
#define SKILL_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "Object.h"
#include "Player.h"
using namespace std;

class Player;

class Skill: public Object
{
private:
    string script;
    int health;
    int magic;
    double attack;
    int defense;
    int cost; // 消耗的 magic
    int hunger;
    //int round;
public:
    Skill();
    Skill(string, int, int, int, int); // third one : attack * int

    /* Virtual function that you need to complete    */
    /* In Item, this function should deal with the   */
    /* pick up action. You should add status to the  */
    /* player.                                       */
    bool triggerEvent(Object*);
    void changeEnemyAttack(double); // attack*double
    void changeEnemyDefense(double);
    bool changeEnemyPoisonedorNot(double);
    /* Set & Get function*/
    void setScript(string);
    string getScript();

    void setHealth(int);
    int getHealth();

    void setAttack(int);
    int getAttack();

    void setDefense(int);
    int getDefense();

    void setCost(int);
    int getCost();

    void setRound(int);
    int getRound();

    void setHunger(int);
};

#endif // SKILL_H_INCLUDED
