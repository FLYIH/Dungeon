#ifndef ENVIRONMENT_H_INCLUDED
#define ENVIRONMENT_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <chrono> // for time
#include <thread> // for time
#include <atomic> // for time
//#include <conio.h> 
// for countdown
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>  
#include "Object.h"
#include "GameCharacter.h"
#include "Player.h"
#include "Item.h"
#include "NPC.h"
#include "Monster.h"
#include "Poison.h"

using namespace std;

class Environment: public GameCharacter
{
private:
    string script;
    vector<Item> commodity;
    vector<NPC> npcs;
    vector<Monster> monsters;
    Poison poison;
public:
    Environment();
    Environment(string, string, vector<Item>, vector<NPC>,vector<Monster>,int ,int ,int ,int, int, int);
    //void listCommodity(); print all the Item in this NPC

    /* Virtual function that you need to complete   */
    /* In NPC, this function should deal with the   */
    /* transaction in easy implementation           */
    bool triggerEvent(Object*);
    //void timerFuncDessert(atomic<bool>& , Player* );

    /* Set & Get function*/
    void setScript(string);
    void setCommodity(vector<Item>);
    void setPoison(Poison);
    string getScript();
    vector<Item> getCommodity();
    Poison getPoison();
    //bool sandStorm(Player*);
    //bool oasis();

};


#endif // ENVIRONMENT_H_INCLUDED
