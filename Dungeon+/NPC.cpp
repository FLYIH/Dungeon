#include "NPC.h"

NPC::NPC() {}

NPC::NPC(string npcName, string npcScript, vector<Item> npcCommodity, int hp, int mp, int attack, int defense, int npchunger, int npcthirst) : 
    GameCharacter(npcName, "npc", 120, hp, 120, mp, attack, defense, npchunger, npcthirst), script(npcScript), commodity(npcCommodity) {}

// could add description
void NPC::listCommodity() { 
    cout << "----------------------------------------------" << endl;
    cout << "\033[1;35mItems available for sale:\033[0m" << endl;
    char option = 'a';
    for (Item item : commodity) {
        cout << option << ". ";
        item.listCommodity();
        option++;
        /*if(item.getName() == "antidote") {
            cout << "   > You provide an animal captured in animal forest in exchange of the item." << endl;
        }*/
    }
    if(getName() != "Rae")
        cout << option << ". I don't want to buy anything" << endl;
}

bool NPC::triggerEvent(Object* obj) {
    // 檢查參數是否是 Player 對象
    Player* player = dynamic_cast<Player*>(obj);
    if(!player) return false;
    cout << getScript() << endl;
    if(getName() == "Schrödinger") {
        cout << "\033[1;35mBeware: it will be the key of the secret room\033[0m" << endl;
        while(1) {
            string ans;
            cout << "Your choice: ";
            cin >> ans;
            if(ans == "2486") {
                cout << "\033[1;33mCorrect\033[0m " << endl;
                if(!commodity.empty()){
                    cout << "You got " << commodity[0].getName() << endl;
                    player->increaseStates(0, 20, 0,0,0,0);
                    player->addItem(commodity[0]);
                    commodity.pop_back();
                }
                return true;
            } else {
                cout << "\033[1;31mWrong\033[0m" << endl;
                if(!player->getPoisoned())
                    poison.triggerEvent(player);
                if(player->getPoisoned()){
                    cout << "Thirst increase 10" << endl;
                    player->increaseStates(0,0,0,0,0,10);
                }
                cout << "\033[1;35mDo you want to try again ? (y / n)\033[0m" << endl;
                bool isValidInput = false;
                char choice;
                do {
                    cout << "Your answer: ";
                    cin >> choice;
                    if(choice == 'y') {
                        isValidInput = true;
                    } else if(choice == 'n') {
                        isValidInput = true;
                        return false;
                    } else {
                        cout << "OOPS, invalid input" << endl;
                    }
                }while(!isValidInput);
            }
        }
        return true;
    }

    listCommodity();
    char ans;
    bool isValidInput = false;
    do{
        cout << "Your choice: ";
        cin >> ans;
        size_t idx = (int)(ans - 'a');
        if(idx == commodity.size()) {
            return false;
        } else if(idx < commodity.size()) {
            if(player->getCoin() >= commodity[idx].getCoin()) {
                //coin
                player->setCoin(player->getCoin() - commodity[idx].getCoin());
                if(!commodity[idx].getOnceUse()) {
                    player->addItem(commodity[idx]);
                }
                
                //use the item
                int HP = commodity[idx].getHealth();
                int MP = 0;
                int ATK = commodity[idx].getAttack();
                int DEF = commodity[idx].getDefense();
                int HUNGER = -commodity[idx].getHunger();
                int THIRST = -commodity[idx].getThirst();
                player->increaseStates(HP, MP, ATK, DEF, HUNGER, THIRST);
                
               
                cout << "Congratulation, you have got the " << commodity[idx].getName() << endl;
                if(commodity[idx].getName() == "milk") {
                    player->setPoisoned(false);
                }
                // when to erase?
                if(!commodity[idx].getOnceUse() || commodity[idx].getName() == "coconut"){
                    commodity.erase(commodity.begin() + (idx));
                }

                cout << "\033[1;35mDo you want another things? (y / n)\033[0m" << endl;
                char ans;
                bool secondIsValidInput = false;
                do {
                    cout << "Your choice: ";
                    cin >> ans;
                    if(ans == 'y') {
                        secondIsValidInput = true;
                        this->triggerEvent(player);
                    } else if(ans == 'n') {
                        secondIsValidInput = true;
                        isValidInput = true;
                    } else {
                        cout << "##############################################" << endl;
                        cout << "#        OOOOOPS!! Please Input Again.       #" << endl;
                        cout << "##############################################" << endl;
                    }
                }while(!secondIsValidInput);
            } else {
                cout << "OOPS! You don't have enough money" << endl << endl;
                this->triggerEvent(player);
            } 
            isValidInput  = true;
        } else if(commodity.size() == 0) {
            cout << "No Item." << endl;
        } else {
            cout << "##############################################" << endl;
            cout << "#        OOOOOPS!! Please Input Again.       #" << endl;
            cout << "##############################################" << endl;
        }
    }while(!isValidInput);

    return true; // 返回 true 表示事件處理成功
}
void NPC::addCommodity(Item newitem) {
    commodity.push_back(newitem);
}

void NPC::popBackCommodity(){
    commodity.pop_back();
}
void NPC::setScript(string npcScript) {
    script = npcScript;
}


void NPC::setPoison(Poison newpoison){
    poison = newpoison;
}

void NPC::setCommodity(vector<Item> npcCommodity) {
    commodity = npcCommodity;
}

string NPC::getScript() {
    return script;
}

vector<Item> NPC::getCommodity() {
    return commodity;
}

Poison NPC::getPoison(){
    return poison;
}