#include "Player.h"
#include "Monster.h"

Player::Player() {
    
}

Player::Player(string newName, string newtag, int newHealth, int newMagic, int newAttack, int newDefense, int newCoin):   
GameCharacter(newName, newtag, 120, newHealth ,120, newMagic,newAttack, newDefense, 0, 0), poisoned(false),coin(newCoin),currentRoom(nullptr), previousRoom(nullptr), map(false){}

void Player::addItem(Item newItem) {
    inventory.push_back(newItem);
}

void Player::addSkill(Skill newSkill) {
    skills.push_back(newSkill);
}

void Player::eraseItem(int idx) {
    inventory.erase(inventory.begin() + idx);
}

int Player::findItem(string newname){
    for (size_t idx = 0; idx < inventory.size(); ++idx) {

        if (newname == inventory[idx].getName()) {
            return idx; 
        }
    }
    return -1; 
}

int Player::findSkill(string newname){
    for (size_t idx = 0; idx < skills.size(); ++idx) {
        if (newname == skills[idx].getName()) {
            return idx; 
        }
    }
    return -1; 
}

void Player::increaseStates(int healthIncrease, int magicIncrease, int attackIncrease, int defenseIncrease, int hungerIncrease, int thirstIncrease) {
    setCurrentHealth(getCurrentHealth() + healthIncrease);
    setCurrentMagic(getCurrentMagic() + magicIncrease);
    setAttack(getAttack() + attackIncrease);
    setDefense(getDefense() + defenseIncrease);
    //may cause the end of the game
    setCurrentHunger(getCurrentHunger() + hungerIncrease);
    setCurrentThirst(getCurrentThirst() + thirstIncrease);
}

void Player::showTwoStates(Object* obj) {
    Monster* monster = dynamic_cast<Monster*>(obj);
    const int width = 23;
   
    cout << "----------------------------------------------" << endl;
    cout << "\033[1;34m" << getTag() << " Status:\033[0m                       "  << "\033[1;31m" << monster->getTag()<<  " Status:\033[0m" << endl;
    cout << getTag() << " [" << getName() << setw(23) << left << "]"  << monster->getTag() << " [" << monster->getName() << "]" << endl;;
    cout << " > HP: " << right << setw(2) << getCurrentHealth() << " / 120"  << "                       > HP: " << monster->getCurrentHealth() << " / " << monster->getMaxHealth() << endl;;
    cout << " > MP: " <<  right << setw(2) << getCurrentMagic()  << " / 120" << "                       > MP: " << monster->getCurrentMagic() << " / 75" << endl;
    cout << " > Attack: " << right << setw(2) << getAttack() << "                         > Attack: " << monster->getAttack() << endl;;
    cout << " > Defense: "  << right << setw(2) << getDefense() << "                        > Defense: " << monster->getDefense() << endl;
    cout << " > Hunger: " << right << setw(2) << getCurrentHunger() << " / "  << getMaxHunger() << "                    > Hunger: NO HUNGER" << endl; // no hunger monster;
    cout << " > Thirst: " << right << setw(2) <<  getCurrentThirst() << " / " <<getMaxThirst() <<  "                    > Thirst: NO THIRST" << endl;
    cout << " > Poisoned: " << right << setw(2);
    if(poisoned) cout << "true                      > Poisoned: NO POISONED" << endl;
    else cout << "false                    > Poisoned: NO POISONED" << endl;
    cout << " > Coins: "<< getCoin() <<  "                          > Coins: NO COIN" <<  endl;
   
    if (!getInventory().empty()) {
        cout << setw(width) << left << " > Items:" << setw(width) << left << "               > Items: NO" << endl;
        for (auto& item : getInventory()) {
            cout << " - " << item.getName() << endl;
        }
    }
    if (!getSkills().empty() || !monster->getSkill().empty()) {
        cout << setw(width) << left <<" > Skills:" <<  "               > Skills: " << endl;
      
        auto playerSkills = getSkills();
        auto monsterSkills = monster->getSkill();
        
        size_t playerIndex = 0;
        size_t monsterIndex = 0;

        while (playerIndex < playerSkills.size() || monsterIndex < monsterSkills.size()) {
            
            if (playerIndex < playerSkills.size()) {
                cout << " - "  << setw(35) << left << playerSkills[playerIndex].getName();
                playerIndex++;
            }
            
            if (monsterIndex < monsterSkills.size()) {
                if(playerIndex <= monsterIndex){
                    cout << setw(38) << left << "";
                }
                cout << "- " << monsterSkills[monsterIndex].getName();
                monsterIndex++;
            }
            cout << endl;
        }
    }
    cout << "----------------------------------------------" << endl;
    cout << endl;
}

void Player::showStates() {
    cout << "----------------------------------------------" << endl;
    cout << "\033[1;34mStatus:\033[0m" << endl;
    cout << getTag() << " [" << getName() << "]" << endl;
    cout << " > HP: " << getCurrentHealth() << " / 120" << endl;
    cout << " > MP: " << getCurrentMagic() << " / 120"<< endl;
    cout << " > Attack: " << getAttack() << endl;
    cout << " > Defense: " << getDefense() << endl;
    cout << " > Hunger: " << getCurrentHunger()  << " / " << getMaxHunger() << endl;
    cout << " > Thirst: " << getCurrentThirst() << " / " << getMaxThirst() << endl;
    cout << " > Poisoned: ";
    if(poisoned) 
        cout << "true" << endl;
    else 
        cout << "false" << endl;
    cout << " > Coins: " << coin << endl;
    if(!inventory.empty()) {
        cout << " \033[1;95m> Items:\033[0m " << endl;
        for (auto& item : inventory) {
            cout << " - " << item.getName() << endl;
        }
    }
    if(!skills.empty()) {
        cout << " \033[1;95m> Skills:\033[0m " << endl;
        for (auto& skill : skills) {
            cout << " - " << skill.getName() << endl;
        }
    }
    cout << "----------------------------------------------" << endl;
    cout << endl;
}

void Player::changeRoom(Room* newRoom) {
    previousRoom = currentRoom;
    currentRoom = newRoom;
}

void Player::Healer(){
    cout << "----------------------------------------------" << endl;
    cout << "|      \033[1;93mBuy something to increase your HP\033[0m     |" << endl;
    cout << "+--------------------------------------------+" << endl;
    cout << "| a. Energy Bar         (HP + 10, Coins - 25)|" << endl;
    cout << "| b. Healing Herb       (HP + 20, Coins - 30)|" << endl;
    cout << "| c. Health Potion      (HP + 30, Coins - 35)|" << endl;
    cout << "| d. Magic Crystal      (HP + 40, Coins - 40)|" << endl;
    cout << "+--------------------------------------------+" << endl;
    char c;
    bool isValidInput = false;        
    do{
        cout << "Your choice: ";
        cin >> c;
        if(c == 'a' || c == 'b' || c == 'c' || c == 'd'){
            int hp = 10*(c - 'a' + 1);
            int playercoins = 25 + 5*(c - 'a');
            if(playercoins > getCoin()){
                cout << "Sorry, you don't have enough money." << endl;
            } else {
                changeHungerSystem();
                setCoin(getCoin() - playercoins);
                increaseStates(hp, 0, 0, 0, 0, 0);
                cout << "HP increase." << endl;
            }
            isValidInput = true;
        } else {
            cout << "##############################################" << endl;
            cout << "#        OOOOOPS!! Please Input Again.       #" << endl;
            cout << "##############################################" << endl;
        }
    }while(!isValidInput);
}

void Player::equipItem(){
    vector<int> index(3);
    index[0] = findItem("shield");
    index[1] = findItem("sword");
    index[2] = findItem("potion");
    vector<Item> newequipment;
   
    if(index[0] != -1 || index[1] != -1 || index[2] != -1){
        cout << "\033[1;32mDo you want to wear the equipment? (y / n)\033[0m " << endl << "Your choice: ";      
        char ans;
        char option = 'a';
        cin >> ans;
        if(ans == 'y'){
            cout << "\033[1;32mWhich one do you want to equip?\033[0m " << endl;

            if(index[0] != -1) {
                newequipment.push_back(inventory[index[0]]);
                cout << option++ << ". " << inventory[index[0]].getName() << endl;
            } 
            if(index[1] != -1){
                newequipment.push_back(inventory[index[1]]);
                cout << option++ << ". "<< inventory[index[1]].getName() << endl;
            } 
            if(index[2] != -1){
                newequipment.push_back(inventory[index[2]]);
                cout << option++ << ". "<< inventory[index[2]].getName() << endl;
            }
            
            
            bool isvalidinput = false;
            char c;
            do{
                cout << "Your choice: ";
                cin >> c;
                size_t n = c - 'a';
                if(n < newequipment.size() && n >= 0){
                    cout << "You equipped the " << newequipment[n].getName();
                    int mp = 0;
                    if(newequipment[n].getName() == "potion") mp = 10;
                    increaseStates(newequipment[n].getHealth(), mp, newequipment[n].getAttack(), newequipment[n].getDefense(),newequipment[n].getHunger(), newequipment[n].getThirst());
                    isvalidinput = true;
                } else {
                    cout << "##############################################" << endl;
                    cout << "#        OOOOOPS!! Please Input Again.       #" << endl;
                    cout << "##############################################" << endl;
                }
            }while(!isvalidinput);
        } 
        cout << endl;
    }
}

bool Player::triggerEvent(Object* object) {
    //list all the item
    if(!inventory.empty()) {
        cout << "\033[1;32mWhich one do you want to use?\033[m" << endl;
        cout << "\033[1mItems:\033[m " << endl;
        char option = 'a';
        for (auto& item : inventory) {
            cout << option << ". ";
            item.listCommodity();
            option++;
        }
        char ans;
        bool isValidInput = false;
        do{
            cout << "\033[1;94;35mDo you want any things? (y / n)\033[m" << endl;
            char ans1;
            bool secondIsValidInput = false;
            do {
                cout << "Your choice: ";
                cin >> ans1;
                if(ans1 == 'y') {
                    secondIsValidInput = true;
                } else if(ans1 == 'n') {
                    secondIsValidInput = true;
                    return true;
                } else {
                    cout << "##############################################" << endl;
                    cout << "#        OOOOOPS!! Please Input Again.       #" << endl;
                    cout << "##############################################" << endl;
                }
                }while(!secondIsValidInput);
            cout << "\033[1;94;35mPress the option if you want to use these things:\033[m ";
            cin >> ans;
            size_t idx = (int)(ans - 'a');
            if(idx < inventory.size()) {
                if(inventory[idx].getName() == "map"){
                    return false;
                } else if(inventory[idx].getName() == "compass") {
                    cout << "nothing happened" << endl;
                    return true;
                } 
                if(coin >= inventory[idx].getCoin()) {
                    //coin
                    coin = coin - inventory[idx].getCoin();
                    //use the item
                    int HP = inventory[idx].getHealth();
                    int MP = 0;
                    int ATK = inventory[idx].getAttack();
                    int DEF = inventory[idx].getDefense();
                    int HUNGER = -inventory[idx].getHunger();
                    int THIRST = -inventory[idx].getThirst();
                    if(inventory[idx].getName() == "potion") {
                        MP = 20;
                    }
                    increaseStates(HP, MP, ATK, DEF, HUNGER, THIRST);
                    //cout << "You use the " << inventory[idx].getName() << endl;
                    inventory[idx].listCommodity();
                    if(inventory[idx].getName() == "milk" || inventory[idx].getName() == "antidote") {
                        if(poisoned) {
                            setPoisoned(false);
                        } else {
                            cout << "Nothing happened. " << endl;
                        }
                    }
                } else {
                    cout << "OOOOOPS!! You don't have enough money" << endl;
                } 
                isValidInput  = true;
            } else {
                cout << "##############################################" << endl;
                cout << "#        OOOOOPS!! Please Input Again.       #" << endl;
                cout << "##############################################" << endl;
            }
        }while(!isValidInput);
    } else {
        cout << "No any item yet" << endl;
    }
    return true; 
}

bool Player::getPoisoned() {
    return poisoned;
}

int Player::getCoin() {
    return coin;
}
void Player::setPoisoned(bool newpoisoned){
    if(newpoisoned)
        cout << "\033[1;34mIn poisoned status.\033[0m" << endl;
    else 
        cout << "\033[1;34mPoisoned status end.\033[0m" << endl;
    poisoned = newpoisoned;
}
void Player::setCoin(int newcoin) {
    coin = newcoin;
    if(coin < 0) coin = 0;
}
void Player::setMap(bool havemap) {
    map = havemap;
}
void Player::setCurrentRoom(Room* newRoom) {
    currentRoom = newRoom;
}

void Player::setPreviousRoom(Room* newRoom) {
    previousRoom = newRoom;
}

Room* Player::getCurrentRoom() {
    return currentRoom;
}

Room* Player::getPreviousRoom() {
    return previousRoom;
}

vector<Item> Player::getInventory() {
    return inventory;
}

vector<Skill> Player::getSkills() {
    return skills;
}

bool Player::getMap() {
    return map;
}

Poison Player::getPoisonstate(){
    return poisonstate;
}

void Player::setPoisonstate(Poison newpoisonstate){
    poisonstate = newpoisonstate;
}

void Player::changeHungerSystem(){
    increaseStates(0,0,0,0,2,2); // hunger + 2, thirst + 2
    if(poisoned){
        if(poisonstate.addCurtime()){
            poisoned = false;
        }
        increaseStates(-poisonstate.getVal(), 0, 0, 0, 0, 0);
    }
}