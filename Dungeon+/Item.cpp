#include "Item.h"
#include "Player.h"

Item::Item() : health(0), attack(0), defense(0){}

Item::Item(string& itemName, int itemHealth, int itemAttack, int itemDefense, int itemhunger, int itemthirst, int itemcoin, bool itemonceuse) : 
Object(itemName, "item") , health(itemHealth),attack(itemAttack), 
defense(itemDefense), hunger(itemhunger), thirst(itemthirst), coin(itemcoin), onceUse(itemonceuse){}

bool Item::triggerEvent(Object* obj) {
    Player* player = dynamic_cast<Player*>(obj);
    if(!player) return false;
    if(!onceUse) {
        player->addItem(*this);
    }
    cout << "----------------------------------------------" << endl;
    if(getName() == "lake") {
        cout << "You find a " << getName() << ". " << endl;
    } else if(getName() == "money") {
        cout << "\033[0;34mCongratulation, you got a lottery. But...\033[0m" << endl;
        cout << "\033[0;34m20 points, guess the number less than 3 times.(included)\033[0m" << endl;
        cout << "\033[0;34m10 points, guess the number less than 5 times.(included)\033[0m" << endl;
        cout << "\033[0;34mnothing, guess the number more than five time.(included)\033[0m" << endl;
        
        int guess;
        int cnt = 0;
        srand(time(NULL));
        int ans = rand() % 100 + 1;
        do{
            cout << "\033[1;32mChoose a number from 1 ~ 100:\033[0m ";
            //cin >> guess;
            while (!(std::cin >> guess)) { 
                cout << "Invalid input. Please enter a valid number: ";
                cin.clear(); 
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            }
            if(guess == ans) {
                cout << "You got ";
                if(cnt <= 3) {
                    player->setCoin(player->getCoin() + 20);
                    cout << "20 ";
                } else if(cnt <= 5) {
                    player->setCoin(player->getCoin() + 10);
                    cout << "10 ";
                }
                cout << "coins" << endl;
                return true;
            }else if(guess > ans && guess <= 100) {
                cout << "Guess less " << endl;
                cnt++;
            } else if(guess < ans && guess > 0){
                cout << "Guess more " << endl;
                cnt++;
            } else {
                cout << "invalid input" << endl;
                cnt++;
            }
        }while(cnt <= 5);
        cout << "Sorry. You have nothing." << endl;
        return true;
    } else {
        cout << "You picked up " << getName() << ". " << endl;
    } 
    player->increaseStates(health, 0, attack, defense, -hunger, -thirst);
    listCommodity();
    if(player->getCurrentRoom()->getIndex() == 3){
        player->setMap(true);
        player->getCurrentRoom()->setIsExit(1);
    }
    return true;
}
void Item::listCommodity() {
    int mp  = 0;
    if(getName() == "potion") mp = 20;
    cout << setw(10) << left << getName() << "( HP: + " << health << ", MP + " << mp << ", ATK + " << attack << ", DEF + " << defense << ", HUNGER - " << hunger << ", THIRST - " << thirst <<" )\t" << coin << " coins" << endl;
}
int Item::getHealth() {
    return health;
}

int Item::getAttack() {
    return attack;
}

int Item::getDefense() {
    return defense;
}

int Item::getHunger() {
    return hunger;
}

int Item::getThirst() {
    return thirst;
}

int Item::getCoin() {
    return coin;
}

void Item::setHealth(int itemHealth) {
    health = itemHealth;
}

void Item::setAttack(int itemAttack) {
    attack = itemAttack;
}

void Item::setDefense(int itemDefense) {
    defense = itemDefense;
}

void Item::setScript(string itemScript) {
    script = itemScript;
}
bool Item::getOnceUse(){
    return onceUse;
}
