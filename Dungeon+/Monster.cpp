#include "Monster.h"
#include "Player.h"

Monster::Monster() {}

Monster::Monster(string monsterName, int maxHP, int curHP, int maxMP,int curMP,int monsterAttack, int monsterDefense) : 
GameCharacter(monsterName, "monster", maxHP,curHP,maxMP, curMP,monsterAttack, monsterDefense, 0, 0) {}

bool Monster::triggerEvent(Object* obj) {
   
    Player* player = dynamic_cast<Player*>(obj);
    if (!player) return false;

    vector<Skill> skills = player->getSkills();
    vector<Item> items = player->getInventory();
    cout << "Wow, you encounter the " << getName() << endl; // show monster information

    player->equipItem();
    while(getCurrentHealth() > 0 && player->getCurrentHealth() > 0) {
        cout << "----------------------------------------------" << endl;
        cout << "|          \033[1;93mWhat do you want to do?\033[0m           |" << endl;
        cout << "+--------------------------------------------+" << endl;
        cout << "| a. flee to previous room                   |" << endl;
        cout << "| b. normal attack                           |" << endl;

        char option = 'c';
        int temp[4] = {0};

        //number 0 skill is normal skill
        for(size_t i = 1; i < skills.size(); i++) { 
            cout << "| " << option << ". use skill " << setw(30) << left << skills[i].getName() << "|" << endl;
            temp[option - 'c'] = i;
            option++;
        }    
        cout << "+--------------------------------------------+" << endl;

        char choice;
        bool validInput = false;
        do {
            // deal with combat
            cout << "Your choice: ";
            cin >> choice; 
            if(choice == 'a') {
                player->changeRoom(player->getPreviousRoom());
                cout << "Back to last room" << endl;
                validInput = true;
                return false;
            } else if(choice == 'b') {
                fight(player, 0);
                validInput = true;
            } else if(temp[choice - 'c'] == 1) {
                fight(player, 1);
                validInput = true;
            } else if(temp[choice - 'c'] == 2) {
                fight(player, 2);
                validInput = true;
            } else if(temp[choice - 'c'] == 3) {
                fight(player, 3);
                validInput = true;
            } else {
                cout << "##############################################" << endl;
                cout << "#        OOOOOPS!! Please Input Again.       #" << endl;
                cout << "##############################################" << endl;
            }
        }while(!validInput);
    }
    //can just come in once
    if(player->getCurrentRoom()->getIndex() != 9 && player->getCurrentRoom()->getIndex() != 2) {
        player->getCurrentRoom()->setIsExit(1);
    }
    if(player->getCurrentHealth() <= 0) return false;
    return true; 
}
void Monster::fight(Player* player, int idx) {
    double monsterDamage;
    double playerDamage;
    // player
    Skill myskill = player->getSkills()[idx];
    if(player->getCurrentMagic() < myskill.getCost()){
        cout << "Sorry, you don't have enough magic. Only use the normal skill. " << endl;
        myskill = player->getSkills()[0];
    }
    //monster 
    srand(time(NULL));
    int random;
    if(getName() == "rabbit" || getName() == "wild boar" || getName() == "deer") {
        random = rand() % 2;
    } else {
        random = rand() % 3;
    }

    Skill monsterskill = skills[random];
    //player attack
    monsterDamage = (player->getAttack() + myskill.getAttack())*(100 - (getDefense() + monsterskill.getDefense()))/100.0 + myskill.getHealth();
    setCurrentHealth(getCurrentHealth() - monsterDamage);
    cout << "\033[1;34mYou do " << monsterDamage << " damages to the " << getName() << "\033[0m"<< endl;
    if(getCurrentHealth() <= 0) { // player win
        cout << "Congratulation! You win " << endl;
        cout << " __        ___                       " << endl;
        cout << " \\ \\      / (_)_ __  _ __   ___ _ __" << endl;
        cout << "  \\ \\ /\\ / /| | '_ \\| '_ \\ / _ \\ '__|" << endl;
        cout << "   \\ V  V / | | | | | | | |  __| |   " << endl;
        cout << "    \\_/\\_/  |_|_| |_|_| |_|\\___|_|   " << endl;

        cout << "You got 30 coins " << endl;
        player->setCoin(player->getCoin() + 30);
        player->increaseStates(0, -myskill.getCost(), 0, 0, 0, 0);
        return;
    }
    //monster atack 
    if(getCurrentMagic() < monsterskill.getCost()){
        monsterskill = skills[0];
    }
    playerDamage = (getAttack() + monsterskill.getAttack())*(100 - (player->getDefense() + myskill.getDefense()))/100.0 + monsterskill.getHealth();
    cout << getName() << " choose skill: " << monsterskill.getName() << endl;
    //may affect the attack of player
    if(monsterskill.getName() == "ferocious charge"){
        cout << "attack decrease" << endl;
        monsterskill.changeEnemyAttack(0.6);
    } else if(monsterskill.getName() == "venom spray") {
        if(monsterskill.changeEnemyPoisonedorNot(0.2)) {
            if(!player->getPoisoned())
                poison.triggerEvent(player);
            else   
                cout << "You have already got poisoned." << endl;
        }
    } else if(monsterskill.getName() == "stench cloud") {
        cout << "attack decrease" << endl;
        cout << "defense decrease" << endl;
        monsterskill.changeEnemyAttack(0.75);
        monsterskill.changeEnemyDefense(0.75);
    }
    //change player's state
    player->increaseStates(-playerDamage, -myskill.getCost(), 0, 0, 0, 0);
    cout  << "\033[1;31m" << getName() << " does " << playerDamage << " damages to you\033[0m" << endl;
    
    //check if poison or not (if poison, will cost another health)
    if(player->getPoisoned()){
        cout << "Since you are poisoned, health --" << endl;
        player->increaseStates(poison.getVal(), 0, 0, 0, 0, 0);
    }
    player->showTwoStates(this);
}

void Monster::addSkill(Skill newskill){
    skills.push_back(newskill);
}

void Monster::setPoison(Poison newpoison){
    poison = newpoison;
}

vector<Skill> Monster::getSkill(){
    return skills;
}

Poison Monster::getPoison(){
    return poison;
}