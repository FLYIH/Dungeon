#ifndef NPC_H_INCLUDED
#define NPC_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
//#include <chrono> // for time
//#include <thread> // for time
//#include <atomic> // for time
#include "GameCharacter.h"
#include "Player.h"
#include "Item.h"
#include "Poison.h"
//#include "Readfile.h"

using namespace std;

class NPC: public GameCharacter
{
private:
    string script;
    vector<Item> commodity;
    Poison poison;
    //vector<Readfile> image;
public:
    NPC();
    NPC(string, string, vector<Item>,int ,int ,int ,int, int, int);
    void listCommodity(); /*print all the Item in this NPC*/

    /* Virtual function that you need to complete   */
    /* In NPC, this function should deal with the   */
    /* transaction in easy implementation           */
    bool triggerEvent(Object*);
    void addCommodity(Item);
    void popBackCommodity();
    //void addImage(Readfile);
    /* Set & Get function*/
    void setScript(string);
    void setCommodity(vector<Item>);
    string getScript();
    void setPoison(Poison);
    vector<Item> getCommodity();
    Poison getPoison();
};


#endif // NPC_H_INCLUDED
