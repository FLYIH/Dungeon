#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <iomanip> // 對齊文本
#include "GameCharacter.h"
#include "Poison.h"
#include "Room.h"
#include "Item.h"
#include "Skill.h"



using  namespace std;

class Item;
class Skill;
class Poison;


class Player: public GameCharacter
{
private:
    bool poisoned;
    int coin;
    Room* currentRoom;
    Room* previousRoom;
    vector<Item> inventory;
    vector<Skill> skills;
    bool map;
    Poison poisonstate;
public:
    Player();
    Player(string,string,int,int,int,int,int);
    void addItem(Item);
    void addSkill(Skill);
    void eraseItem(int);
    int findItem(string);
    int findSkill(string);
    void increaseStates(int,int,int,int,int,int);
    void showTwoStates(Object*);
    void showStates();
    void changeRoom(Room*);
    void Healer();
    void equipItem();
    /* Virtual function that you need to complete   */
    /* In Player, this function should show the     */
    /* status of player.                            */
    bool triggerEvent(Object*);
    
    /* Set & Get function*/
    void setMyName(string&);
    int getCoin();
    bool getPoisoned();
    void setCurrentRoom(Room*);
    void setPreviousRoom(Room*);
    void setPoisoned(bool);
    void setCoin(int);
    void setMap(bool);
    Room* getCurrentRoom();
    Room* getPreviousRoom();
    vector<Item> getInventory();
    vector<Skill> getSkills();
    bool getMap();
    Poison getPoisonstate();
    void setPoisonstate(Poison);
    void changeHungerSystem();
};

#endif // PLAYER_H_INCLUDED
