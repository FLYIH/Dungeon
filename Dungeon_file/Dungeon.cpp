#include "Dungeon.h"

Dungeon::Dungeon() : finishGame(false){}
bool Dungeon::checkGameLogic() {
    // 檢查遊戲是否應該結束，包括玩家勝利、或者他/她死亡
    /*
    win : 
    1. finish all room and all passed 
    lose :
    health < 0 
    */
    if(player.getCurrentHealth() <= 0) {
        return false;
    } 
    if(finishGame) {
        return false;
    }
    //also add another finish condition
    return true; // continue
}

void Dungeon::createPlayer() {
    // startgame
    string name;
    cout << "\033[1;35mPlease Enter Your Name:\033[0m " << endl;
    getline(cin, name);
    
    cout << endl << "Hi, " << name << " . Welcome to " << endl << endl;
    welcomeMessage.addFileName("welcome.txt");
    welcomeMessage.printFile(0);
    unordered_map<string, vector<int>> occupations = {
        {"sarrior", {100, 50, 20, 15, 50}}, // HP, MP, Attack, Defense,coin
        {"mage", {80, 100, 15, 10, 50}},
        {"rogue", {90, 70, 18, 12, 50}}    
    };
    unordered_map<string, pair<string, vector<int>>> skills = {
        {"warrior", {{"Power Strike"}, {30, 0, 0, 20}}},
        {"mage", {{"Fireball"}, {20, 0, 0, 10}}},
        {"rogue", {{"Backstab"}, {25, 0, 0, 15}}}
    };
    
    cout << "\033[1;35mOccupation:\033[0m " << "Warrior" << endl;
    cout << "  HP: 100" << endl;
    cout << "  MP: 50" << endl;
    cout << "  Attack: 20" << endl;
    cout << "  Defense: 15" << endl;
    cout << "  Coins: 50" << endl;
    cout << "  Hunger: " << "0 / 50" << endl;
    cout << "  Thirst: " << "0 / 50" << endl;
    cout << "  Poisoned : ";
    if(player.getPoisoned()) cout << "true" << endl;
    else cout << "false" << endl;
    cout << endl;
    /*string role;
    bool isValidInput = false;
    do {
        cout << "----------------------------------------------" << endl;
        cout << "Please Choose Your Occupation: (Type The Name)" << endl;
        //show the occupation
        for (const auto& occupation : occupations) {
            cout << "Occupation: " << occupation.first << endl;
            cout << "  HP: " << occupation.second[0] << endl;
            cout << "  MP: " << occupation.second[1] << endl;
            cout << "  Attack: " << occupation.second[2] << endl;
            cout << "  Defense: " << occupation.second[3] << endl;
            cout << " Coins: " << occupation.second[4] << endl;
            cout << "  Hunger: " << "0 / 50" << endl;
            cout << "  Thirst: " << "0 / 50" << endl;
            cout << endl;
        }
        cin >> role;
        
        if(occupations.find(role) != occupations.end()) {
            player = Player(name, role, occupations[role][0], occupations[role][1], occupations[role][2], occupations[role][3],occupations[role][4]); 
            Skill newskill(skills[role].first, skills[role].second[0], skills[role].second[1], skills[role].second[2], skills[role].second[3]);
            player.addSkill(newskill);
            isValidInput = true;
        } else {
            cout << "----------------------------------------------" << endl;
            cout << "OOOOOPS!! Please Input Again." << endl;
            cout << endl;
        }
    }while(!isValidInput);*/
    
    //player.showStates();
    player = Player(name, "warrior",100,50,20,15,50); 
    Skill normal("NormalSkill", 0, 0, 0, 0);
    player.addSkill(normal);
    Skill powerStrike("PowerStrike", 30, 0, 0, 10);
    player.addSkill(powerStrike);
    // this is test
    /*player = Player("elaine", "warrior",100,50,20,15,50); 
    Skill normal("normal skill", 0, 0, 0, 0);
    player.addSkill(normal);
    Skill powerStrike("power strike", 30, 0, 0, 10);
    player.addSkill(powerStrike);*/
    //player.showStates();
}
void readText(vector<string>& object, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {

        int numLines;
        file >> numLines;
        file.ignore();  // 忽略换行符

        string line;
        for (int i = 0; i < numLines; ++i) {
            getline(file, line);
            object.push_back(line);
        }
        file.close();
    } else {
        cerr << "Unable to open file " << filename << endl;
    }
}
void Dungeon::createMap() {
    // set the items in room
    // set the monster in room
    // set the npc in room

    //create 10 maps
    for(int i = 0; i < 10; i++) {
        maps.addFileName("map" + to_string(i) + ".txt");
    }
        
    vector<string> item;
    vector<string> npc; // script and name  (name, script) (name, script)
    vector<string> monster;
    vector<string> env; // script and name
    readText(item, "Item.txt");
    readText(npc, "NPC.txt");
    readText(monster, "Monster.txt");
    readText(env, "Environment.txt");

    vector<Object *> objects[10];
    //room 0
    // i just put the warror's skill only
    objects[0].push_back(new Item(item[0], 0, 0, 0, 0, 0, 0, true)); // money
    objects[0].push_back(new Item(item[1], 20, 0, 0, 0, 0, 10, false)); // cake
    objects[0].push_back(new Skill("BattleCry", 0, 20, 10, 30)); // skill three warrior
    imagefile.addFileName("warriorskill1.txt");
    //room 1
    vector<Item> easttownItems;
    vector<NPC> easttownNPC;
    vector<Monster> easttownMonster;
    //easttownItems.push_back(Item(item[2], 0, 0, 0, 0, 0, 30, false)); // milk
    // easttownItems.push_back(Item(item[3], 0, 0, 0, 0, 0, 0, false)); // antidote
    //easttownItems.push_back(Item(item[4], -20, 0, 0, 0, 0, 0, true)); //coward  仍然poisoned狀態
    easttownNPC.push_back(NPC(npc[0], npc[1], easttownItems, 0, 0, 0, 0, 0, 0)); //Rae
    objects[1].push_back(nullptr);
    Environment* easttownenv = new Environment(env[0], env[1], easttownItems, easttownNPC, easttownMonster,0,0,0,0,0,15);
    easttownenv->setPoison(Poison("venomous", 3, 10));
    objects[1].push_back(easttownenv); //in poison status
    imagefile.addFileName("wantpost.txt");
    //room 2
    // 2.1
    vector<Item> monsterForest1Items;
    vector<NPC> monsterForest1NPC;
    vector<Monster> monsterForest1Monster;
    monsterForest1Items.push_back(Item(item[5], 0, 0, 0, 0, 20, 0, true)); //lake
    monsterForest1Monster.push_back(Monster(monster[0],80, 80 ,50, 50, 20, 10)); // tiger
    Skill normal("NormalSkill", 0, 0, 0, 0);
    Skill bite("bite", 30, 0, 0, 10); // need another
    Skill roar("roar", 20, 0, 0, 5);
    monsterForest1Monster[0].addSkill(normal);
    monsterForest1Monster[0].addSkill(bite);
    monsterForest1Monster[0].addSkill(roar);
    objects[2].push_back(new Environment(env[2], env[3], monsterForest1Items, monsterForest1NPC, monsterForest1Monster, 0,0,0,0,5, 0));
    // 2.2
    vector<Item> monsterForest2Items;
    vector<NPC> monsterForest2NPC;
    vector<Monster> monsterForest2Monster;
    monsterForest2Items.push_back(Item(item[6], 0, 0, 0, 5, 0, 5, false)); // rabbit
    monsterForest2Items.push_back(Item(item[7], 0, 10, 0, 0, 0, 10, false)); // wild boar
    monsterForest2Items.push_back(Item(item[8], 0, 0, 0, 10, 0, 10, false)); // deer
    monsterForest2Monster.push_back(Monster(monster[1], 50, 50, 10, 10, 15, 5)); // rabbit
    monsterForest2Monster.push_back(Monster(monster[2], 100, 100, 20, 20, 25, 20)); // wild boar
    monsterForest2Monster.push_back(Monster(monster[3], 80, 80, 30, 30, 30, 15)); // deer
  
    Skill jumping("JumpingStrike", 20, 0, 0, 5);
    jumping.setHunger(20);
    Skill charge("FerociousCharge", 35, 0, 0, 10);
    //charge.changeEnemyAttack(0.6);
        //player's damage has not finished
    Skill dodge("AgileDodge", 30, 0, 0, 10);
    monsterForest2Monster[0].addSkill(normal);
    monsterForest2Monster[1].addSkill(normal);
    monsterForest2Monster[2].addSkill(normal);
    monsterForest2Monster[0].addSkill(jumping);
    monsterForest2Monster[1].addSkill(charge);
    monsterForest2Monster[2].addSkill(dodge);
    objects[2].push_back(new Environment(env[4], env[5], monsterForest2Items, monsterForest2NPC, monsterForest2Monster,0,0,0,0,5, 0));
    //room 3
    objects[3].push_back(new Item(item[9], 0,0,0,0,0,0,false)); // map
        //deal with second in! isexist?
    //room 4
    Monster* cavemonster = new Monster(monster[4], 90, 90, 20, 20, 30, 10); // zombie
    Skill grasp("DecayingGrasp", 40, 0, 0, 10);
    Skill infect("InfectedBite", 25, 0, 0, 15);
    cavemonster->addSkill(normal);
    cavemonster->addSkill(grasp);
    cavemonster->addSkill(infect);
    objects[4].push_back(cavemonster);
    objects[4].push_back(new Item(item[10], 0, 10, 0, 0, 0, 10, false)); // sword
    objects[4].push_back(new Item(item[16], 10, 0, 0, 0, 0, 5, false)); // berry
    //room 5
    vector<Item> secretItems;
    secretItems.push_back(Item(item[2], 0, 0, 0, 0, 0, 30, false)); // milk
    objects[5].push_back(new NPC(npc[2], npc[3], secretItems, 0, 0, 0, 0, 0, 0)); // 
    //room 6
    //6.1
    vector<Item> sandstormItems;
    vector<NPC> sandstormNPC;
    vector<Monster> sandstormMonster;
    sandstormItems.push_back(Item(item[11], 0, 0, 0, 0, 0, 20, false)); //compass
    objects[6].push_back(new Environment(env[6], env[7], sandstormItems, sandstormNPC,sandstormMonster,0,0,0,0,5,10));
    //6.2
    vector<Item> oasisItems;
    vector<NPC> oasisNPC;
    vector<Monster> oasisMonster;
    //oasisItems.push_back(Item(item[12], 0, 0, 0, 0, 20, 0, true)); // coconut
    oasisItems.push_back(Item(item[13], 0, 0, 0, 20, 0, 10, false)); // bread
    oasisItems.push_back(Item(item[14], 0, 0, 0, 0, 20, 10, false)); // water
    oasisNPC.push_back(NPC(npc[4], npc[5], oasisItems, 0, 0, 0, 0, 0, 0));  // it cause segmentation error
    objects[6].push_back(new Environment(env[8], env[9], oasisItems, oasisNPC, oasisMonster,0,0,0,0,2,2));
    //7
    objects[7].push_back(new Item(item[17], 0, 0, 10, 0, 0, 10, false));
    //8
    vector<Item> labItems;
    labItems.push_back(Item(item[15], 0, 0, 0, 0, 0, 10, false)); //potion
    NPC* labnpc = new NPC(npc[6], npc[7], labItems, 0, 0, 0, 0, 0, 0); // shrodinger
    labnpc->setPoison(Poison("spore", 2, 10));
    objects[8].push_back(labnpc); //Schrödinger
    objects[8].push_back(new Skill("ShieldBlock", 0, 20, 10, 30));
    imagefile.addFileName("riddle.txt");
    imagefile.addFileName("warriorskill2.txt");
    //room 9
    //9.1
    vector<Item> stuckItems;
    vector<NPC> stuckNPC;
    vector<Monster> stuckMonster;
    objects[9].push_back(new Environment(env[10], env[11], stuckItems, stuckNPC, stuckMonster,0,0,0,0,10,0)); //stuck 
    //9.2
    stuckMonster.push_back(Monster(monster[5], 90, 90, 40, 40, 35, 25)); // mummy
    stuckMonster[0].addSkill(normal);
    stuckMonster[0].addSkill(Skill("VenomSpray", 30, 0, 0, 15)); // got poisoned or not
    stuckMonster[0].setPoison(Poison("acid", 4, 10));
    stuckMonster[0].addSkill(Skill("StenchCloud", 0, 0, 0, 20)); 
        //swampMonster->getSkill()[1].changeEnemyAttack(0.75);
        //swampMonster->getSkill()[1].changeEnemyDefense(0.75);
    objects[9].push_back(new Environment(env[12], env[13], stuckItems, stuckNPC, stuckMonster,0,0,0,0,10,0)); //mummy swamp
    imagefile.addFileName("mummyfile.txt"); // 4
    

    for (int i = 0; i < 10; i++) {
        Room room(0, i, objects[i]);
        rooms.push_back(room);
    }
    // secret room
    rooms[5].setIsExit(1);
    
    player.setCurrentRoom(&rooms[7]);
    
    //push objects to room
    for(int i = 0;i<=9;i++){
        rooms[i].setObjects(objects[i]);
    }
    /*rooms[0].setObjects(objects[0]);
    rooms[1].setObjects(objects[1]);
    rooms[2].setObjects(objects[2]);
    rooms[2].setObjects(objects[2]);
    rooms[6].setObjects(objects[6]);*/

    //set the relation between different rooms
    // Room 0: WestTown (merchant)
    rooms[0].setRightRoom(&rooms[1]);
    rooms[0].setDownRoom(&rooms[3]);

    // Room 1: EastTown (enemy)
    rooms[1].setRightRoom(&rooms[2]);
    rooms[1].setLeftRoom(&rooms[0]);
    rooms[1].setDownRoom(&rooms[4]);

    // Room 2: Forest (food)
    rooms[2].setLeftRoom(&rooms[1]);
    rooms[2].setDownRoom(&rooms[5]);

    // Room 3: hotel
    rooms[3].setUpRoom(&rooms[0]);
    rooms[3].setRightRoom(&rooms[4]);
    rooms[3].setDownRoom(&rooms[6]);

    // Room 4: Cave (boss)
    rooms[4].setUpRoom(&rooms[1]);
    rooms[4].setLeftRoom(&rooms[3]);
    rooms[4].setRightRoom(&rooms[5]);
    rooms[4].setDownRoom(&rooms[7]);

    // Room 5: Secret
    rooms[5].setUpRoom(&rooms[2]);
    rooms[5].setLeftRoom(&rooms[4]);
    rooms[5].setDownRoom(&rooms[8]);

    // Room 6: Dessert
    rooms[6].setUpRoom(&rooms[3]);
    rooms[6].setRightRoom(&rooms[7]);
    

    // Room 7: Start Place
    rooms[7].setUpRoom(&rooms[4]);
    rooms[7].setLeftRoom(&rooms[6]);
    rooms[7].setRightRoom(&rooms[8]);
    rooms[7].setDownRoom(&rooms[9]);

    // Room 8: Lab (藥水)
    rooms[8].setUpRoom(&rooms[5]);
    rooms[8].setLeftRoom(&rooms[7]);

    // Room 9: swamp
    rooms[9].setUpRoom(&rooms[7]);
    
}

void Dungeon::handleMovement() {
    // player action
    char option = 'a';
    char temp[5] = {0};
    cout << "+--------------------------------------------+" << endl;
    cout << "|          \033[1;93mWhere do you want to go?\033[0m          |" << endl;
    cout << "+--------------------------------------------+" << endl;

    if (player.getCurrentRoom()->getUpRoom() != nullptr) {
        cout << "| " << option <<  setw(42) << left << ". Go up" << "|" << endl;
        temp[option - 'a'] = '1';
        option++;
    }
    if (player.getCurrentRoom()->getDownRoom() != nullptr) {
        cout << "| " << option << setw(42) << left << ". Go down" <<  "|" << endl;
        temp[option - 'a'] = '2';
        option++;
    }
    if (player.getCurrentRoom()->getLeftRoom() != nullptr) {
        cout << "| " << option << setw(42) << left << ". Go left" << "|" << endl;
        temp[option - 'a'] = '3';
        option++;
    }
    if (player.getCurrentRoom()->getRightRoom() != nullptr) {
        cout << "| " << option << setw(42) << left << ". Go right" <<  "|" << endl;
        temp[option - 'a'] = '4';
        option++;
    }

    cout << "+--------------------------------------------+" << endl;
    
    char choice;
    bool isValidInput = false;
    do {
        cout <<  "Your choice: ";
        cin >> choice;

        switch (temp[choice - 'a'])
        {
        case '1':
            player.changeRoom(player.getCurrentRoom()->getUpRoom());
            isValidInput = true;
            break;
        case '2':
            player.changeRoom(player.getCurrentRoom()->getDownRoom());
            isValidInput = true;
            break;
        case '3':
            player.changeRoom(player.getCurrentRoom()->getLeftRoom());
            isValidInput = true;
            break;
        case '4':
            player.changeRoom(player.getCurrentRoom()->getRightRoom());
            isValidInput = true;
            break;
        default:
            cout << "##############################################" << endl;
            cout << "#        OOOOOPS!! Please Input Again.       #" << endl;
            cout << "##############################################" << endl;
            break;
        }
    }while(!isValidInput);
    
    player.changeHungerSystem();
    
}

void Dungeon::handleEvent(Object* object) {
    // 處理玩家與房間中物體的互動
    player.increaseStates(0,0,0,0,2,2); // hunger + 2, thirst + 2
    if(object == nullptr) { 
        if(player.getCurrentRoom()->getIndex() == 5) {
            welcomeMessage.addFileName("end.txt");
            welcomeMessage.printFile(1);
            finishGame = true;
        }
    } else {
        if(object->getTag() == "warrior") {
            if(!player.triggerEvent(&player)){
                maps.printFile(player.getCurrentRoom()->getIndex());
            }
        }else if(object->getTag() == "monster") {
            if(!object->triggerEvent(&player)) {
                //lose
                //finishGame = true;  maybe flee
            } else if(object->getName() == "zombie") {
                handleEvent(player.getCurrentRoom()->getObjects()[1]);
                handleEvent(player.getCurrentRoom()->getObjects()[2]);
            }
        } else if(object->getTag() == "environment") {
            if(object->getName() == "stuck") {
                if(!object->triggerEvent(&player)) {
                    // fail to pass
                    handleEvent(player.getCurrentRoom()->getObjects()[1]);
                    rooms[9].popBackObject();
                    rooms[9].addObject(nullptr);
                }
            } else if(object->getName() == "mummy swamp"){
                imagefile.printFile(4);
                object->triggerEvent(&player);
                imagefile.deleteFile(4);
            } else {
                // in secret
                object->triggerEvent(&player);
                
            }
        } else if(object->getTag() == "npc"){
            if(object->getName() == "Schrödinger") {
                //in lab
                imagefile.printFile(2);
                if(object->triggerEvent(&player)) {
                    //change the skill to nullptr
                    handleEvent(player.getCurrentRoom()->getObjects()[1]);
                    rooms[8].popBackObject();
                    rooms[8].addObject(nullptr);
                } 
            } else {
                if(object->triggerEvent(&player)){
                    rooms[5].popBackObject();
                    rooms[5].addObject(nullptr);
                }
            }
        } else if(object->getTag() == "item") {
            object->triggerEvent(&player);
            if(object->getName() == "shield") {
                // start room
                rooms[7].popBackObject();
                rooms[7].addObject(nullptr);
            } 
        } else if(object->getTag() == "skill") {
            if(player.findSkill(object->getName()) == -1) {
                Skill* skill = dynamic_cast<Skill*>(object);
                player.addSkill(*skill);
                cout << "You picked up the skill " << skill->getName() << endl;
                if(player.getTag() == "warrior" && player.getCurrentRoom()->getIndex() == 0) {
                    imagefile.printFile(0); 
                } else if(player.getTag() == "warrior" && player.getCurrentRoom()->getIndex() == 8) {
                    imagefile.printFile(3);
                }
            } else {
                cout << "You have got the skill." << endl;
            }
        }
    }  
}

bool isFileEmpty(const string& filename) {
    std::ifstream file(filename);
    return file.peek() == std::ifstream::traits_type::eof();
}

void Dungeon::startGame() {
    // 處理整個遊戲的初始設置，包括創建玩家、創建地圖等
    /*
    give some description (可以讀檔案)
    */
    // need to finish
    createPlayer();
    createMap();
    if(!isFileEmpty("saveplayer.txt")) {
        char c;
        cout << "\033[1;33mDo you want to go back to last place you play? (y / n)\033[0m " << endl;
        cin >> c;
        if(c == 'y'){
            record.loadFromFile(&player, rooms);
        }
        ofstream file1("saveplayer.txt",ios::trunc);
        file1.close();
    }
    
}

void Dungeon::chooseAction(vector<Object*> objects) {
    // 處理玩家的動作，包括顯示房間中可以進行的動作列表和處理玩家的輸入
    /*
    the monster may have died or not
    */
    /*cout << "----------------------------------------------" << endl;
    cout << "What do you want to do ?" << endl;
    cout << "a. Move" << endl;
    cout << "b. Check Status" << endl;
    cout << "c. Open Backpack" << endl;
    cout << "d. Show Map" << endl;
    cout << "e. Exit the Game" << endl;*/
    cout << "----------------------------------------------" << endl;
    cout << "|          \033[1;93mWhat do you want to do ?\033[0m          |" << endl;
    cout << "+--------------------------------------------+" << endl;
    cout << "| a. Move                                    |" << endl;
    cout << "| b. Check Status                            |" << endl;
    cout << "| c. Open Backpack                           |" << endl;
    cout << "| d. Health Station                          |" << endl;
    cout << "| e. Exit the Game                           |" << endl;
    cout << "+--------------------------------------------+" << endl;
    char choice;
    bool isValidInput = false;
    //bool secondisValidInput = false;
    do {
        cout << "Your choice: ";
        cin >> choice; 
        
        switch (choice)
        {
        case 'a':
            handleMovement(); 
            //player.getCurrentRoom()->showWelcomeMessage();
            if(!checkGameLogic()) {
                break;
            }
            // only one monster/item in one room
            if(!player.getCurrentRoom()->getIsExit()) {
                player.getCurrentRoom()->showWelcomeMessage();
                srand(time(NULL));
                //temp
                int random = 0;
                if(player.getCurrentRoom()->getIndex() == 0) {
                    random = rand() % 3;
                } else if(player.getCurrentRoom()->getIndex() == 1) {
                    imagefile.printFile(1);
                    bool isValidInput1 = false;
                    char c;
                    do{
                        cout << "Your choose: ";
                        cin >> c;
                        if(c == 'a') {
                            cout << "hunger increase." << endl;
                            player.increaseStates(0,0,0,0,30,0);
                            random = 0; // nullptr
                            isValidInput1 = true;
                        } else if(c == 'b') {
                            random = 1; 
                            isValidInput1 = true;
                        } else {
                            cout << "##############################################" << endl;
                            cout << "#        OOOOOPS!! Please Input Again.       #" << endl;
                            cout << "##############################################" << endl;
                        }
                    }while(!isValidInput1);
                } else if(player.getCurrentRoom()->getIndex() == 4 || player.getCurrentRoom()->getIndex() == 5 || player.getCurrentRoom()->getIndex() == 3 || player.getCurrentRoom()->getIndex() == 8 || player.getCurrentRoom()->getIndex() == 9){
                    random = 0;
                } else {
                    random = rand() % 2;
                }

                handleEvent(player.getCurrentRoom()->getObjects()[random]);
                
                //(0) 0 money 1 cake 2 skill
                //(1) 0 nullptr 1 poisonstate
                //(2) 0 magic forest 1 animal forest
                //(3) 0 getmap
                //(4) 0 zonbie (1 sword 2 berry)
                //(5) 0 milk
                //(6) 0 sandstorm   1 oasis
                //(8) 0 Schrödinger 1 skill
                //(9) 0 stuck 1 monster 2 flood(not finish)
            } else {
                if(player.getCurrentRoom()->getIndex() == 5){
                    cout << "\033[1;34mPlease enter the key number that you got from Schrödinger (lab) to open the secret room:\033[0m ";
                    string number;
                    cin >> number;
                    if(number == "2486"){
                        rooms[5].setIsExit(0);
                        handleEvent(player.getCurrentRoom()->getObjects()[0]);
                    } else {
                        cout << "\033[1;31mWrong\033[0m" << endl;
                    }
                } else
                    cout << "You have experienced this room. " << endl;
            }
            isValidInput = true;
            break;
        case 'b':
            player.showStates();
            player.changeHungerSystem();
            isValidInput = true;
            break;
        case 'c':
            handleEvent(&player);
            player.changeHungerSystem();
            isValidInput = true;
            break;
        case 'd':
            player.Healer();
            isValidInput = true;
            break;
        case 'e':
            finishGame = true;
            isValidInput = true;
            record.saveToFile(&player, rooms);
            break;
        default:
            cout << "##############################################" << endl;
            cout << "#        OOOOOPS!! Please Input Again.       #" << endl;
            cout << "##############################################" << endl;
            break;
        }
    }while(!isValidInput);
    
}

void Dungeon::runDungeon() {
    // 處理整個遊戲流程
    startGame();
    
    while(checkGameLogic()) {
        chooseAction(player.getCurrentRoom()->getObjects());
    }
    // game over
    //player.showStates();
    if(player.getCurrentHealth() == 0) {
        cout << "$$\\       $$$$$$\\   $$$$$$\\  $$$$$$$$\\ $$$$$$$\\  " << endl;
        cout << "$$ |     $$  __$$\\ $$  __$$\\ $$  _____|$$  __$$\\ " << endl;
        cout << "$$ |     $$ /  $$ |$$ /  \\__|$$ |      $$ |  $$ |" << endl;
        cout << "$$ |     $$ |  $$ |\\$$$$$$\\  $$$$$\\    $$$$$$$  |" << endl;
        cout << "$$ |     $$ |  $$ | \\____$$\\ $$  __|   $$  __$$< " << endl;
        cout << "$$ |     $$ |  $$ |$$\\   $$ |$$ |      $$ |  $$ |" << endl;
        cout << "$$$$$$$$\\ $$$$$$  |\\$$$$$$  |$$$$$$$$\\ $$ |  $$ |" << endl;
        cout << "\\________|\\______/  \\______/ \\________|\\__|  \\__|" << endl << endl;
        cout << "Game Over." << endl;
    } 
}