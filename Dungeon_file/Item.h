#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <limits> // deal with cin problem
#include "Object.h"

using namespace std;

class Player;

class Item: public Object
{
private:
    int health,attack,defense,hunger,thirst;
    int coin;
    bool onceUse;
    string script;
public:
    Item();
    Item(string&, int, int, int , int, int, int, bool);

    /* Virtual function that you need to complete    */
    /* In Item, this function should deal with the   */
    /* pick up action. You should add status to the  */
    /* player.                                       */
    bool triggerEvent(Object*);
    void listCommodity();
    /* Set & Get function*/
    int getHealth();
    int getAttack();
    int getDefense();
    int getHunger();
    int getThirst();
    int getCoin();
    string getScript();
    void setHealth(int);
    void setAttack(int);
    void setDefense(int);
    void setScript(string);
    bool getOnceUse();
};

#endif // ITEM_H_INCLUDED
