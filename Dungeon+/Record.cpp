#include "Record.h"

Record::Record() {}

void Record::savePlayer(Player* player, ofstream& file) {
    // Save player information to file
    file << player->getName() << " " << player->getCurrentHealth() << " " << player->getCurrentMagic() << " " << player->getAttack() << " " 
    << player->getDefense() << " " << player->getCurrentHunger() << " " << player->getCurrentThirst() << " " << player->getPoisoned() << " " << player->getCoin() << "\n";

    // Save player poison state to file
    if(player->getPoisoned()){
        Poison poison = player->getPoisonstate();
        file << poison.getName() << " " << poison.getVal() << " " << poison.getDuration() << " " << poison.getCurtime() << "\n";
    }
    // Save player inventory to file
    int itemidx = player->getInventory().size();
    vector<Item> inventory = player->getInventory();
    file << itemidx << "\n";
    for (auto& item : inventory) {
        file << item.getTag() << " " << item.getName() << " " << item.getHealth() << " " << item.getAttack() << " " << item.getDefense() << " " << item.getHunger() << " " << item.getThirst() << " " << item.getCoin() << " " << item.getOnceUse()<<"\n";
    }
    
    // Save player skills to file
    vector<Skill> skills = player->getSkills();
    int skillidx = player->getSkills().size();
    file << skillidx << "\n";
    for (auto& skill : skills) {
        file << skill.getTag() << " " << skill.getName() << " " << skill.getHealth() << " " << skill.getAttack() << " " << skill.getDefense() << " " << skill.getCost() << "\n";
    }

}


void Record::loadPlayer(Player* player, ifstream& file) {
    string name;
    int health, magic, attack, defense, hunger, thirst, coin;
    bool ispoisoned;
    // Read player information from file
    file >> name >>  health >> magic >> attack >> defense >> hunger >> thirst >> ispoisoned >> coin;
    player->setName(name);
    player->setCurrentHealth(health);
    player->setCurrentMagic(magic);
    player->setAttack(attack);
    player->setDefense(defense);
    player->setCurrentHunger(hunger);
    player->setCurrentThirst(thirst);
    if(ispoisoned)
        player->setPoisoned(ispoisoned); // check
    player->setCoin(coin);


    // Read player poison state from file
    if(ispoisoned){
        int val, duration, curtime;
        string line1;
        getline(file, line1);
        stringstream ss1(line1);
        string poisonname;
        ss1 >> poisonname >> val >> duration >> curtime;
        player->setPoisonstate(Poison(poisonname, val, duration));
        player->getPoisonstate().setCurtime(curtime);
    }
    
    // Read player inventory from file
    int itemnum;

    file.ignore(numeric_limits<streamsize>::max(), '\n'); // 消耗換行符號
    file >> itemnum;

    string itemtag, itemName;
    int itemhp, itematk, itemdef, itemhunger, itemthirst, itemcoin;
    bool itemonceuse;
    
    for (int i = 0; i < itemnum; ++i) {
        file.ignore(numeric_limits<streamsize>::max(), '\n'); // 消耗換行符號
        file >> itemtag >> itemName >> itemhp >> itematk >> itemdef >> itemhunger >> itemthirst >> itemcoin >> itemonceuse;
        player->addItem(Item(itemName, itemhp, itematk, itemdef, itemhunger, itemthirst, itemcoin, itemonceuse));
    }

    
    int skillnum;
    file.ignore(numeric_limits<streamsize>::max(), '\n'); // 消耗換行符號
    file >> skillnum;
  
    for (int i = 0; i < skillnum; ++i) {
        string skilltag, skillName;
        int skillhp, skillatk, skilldef, skillcost;
        file.ignore(numeric_limits<streamsize>::max(), '\n'); // 消耗換行符號
        file >> skilltag >> skillName >> skillhp >> skillatk >> skilldef >> skillcost;
        if(player->findSkill(skillName) == -1){
            player->addSkill(Skill(skillName, skillhp, skillatk, skilldef, skillcost));
        }
    }
    file.ignore(numeric_limits<streamsize>::max(), '\n'); // 消耗換行符號
    
}



void Record::saveToFile(Player* player, vector<Room>& rooms) {
    ofstream file1("saveplayer.txt");
    //ofstream file2("saveroom.txt");
    
    savePlayer(player, file1);
    ///saveRooms(rooms, file2);
    file1.close();
    //file2.close();
}

void Record::loadFromFile(Player* player, vector<Room>& rooms) {
    ifstream file1("saveplayer.txt");
    //ifstream file2("saveroom.txt");
    
    loadPlayer(player, file1);
    //loadRooms(rooms, file2);
    file1.close();
    //file2.close();
}
