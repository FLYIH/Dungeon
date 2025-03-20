#ifndef DUNGEON_H_INCLUDED
#define DUNGEON_H_INCLUDED

#include <iostream>
#include <unordered_map>
#include <fstream>
#include <utility>//pair
#include <string>
#include <vector>
#include <exception>
#include <limits> // deal with cin problem
#include "Poison.h"
#include "Player.h"
#include "Readfile.h"
#include "Monster.h"
#include "NPC.h"
#include "Environment.h"
#include "Item.h" 
#include "Room.h"
#include "Record.h"


using namespace std;

class Dungeon{
private:
    Player player;
    Readfile imagefile;
    Readfile welcomeMessage;
    Readfile maps;
    vector<Room> rooms;
    bool finishGame;
    Record record;
public:
    Dungeon();
    /* Create a new player, and give him/her basic status */
    void createPlayer();

    /* Create a map, which include several different rooms */
    void createMap();

    /* Deal with player's moveing action */
    void handleMovement();

    /* Deal with player's iteraction with objects in that room */
    void handleEvent(Object*);

    /* Deal with all game initial setting       */
    /* Including create player, create map etc  */
    void startGame();

    /* Deal with the player's action     */
    /* including showing the action list */
    /* that player can do at that room   */
    /* and dealing with player's input   */
    void chooseAction(vector<Object*>);
    //void showMap(int);
    /* Check whether the game should end or not */
    /* Including player victory, or he/she dead */
    bool checkGameLogic();

    /* Deal with the whole game process */
    void runDungeon();
};


#endif // DUNGEON_H_INCLUDED
