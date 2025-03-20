#include "Poison.h"
#include "Player.h"
// Default constructor
Poison::Poison() : val(0), duration(0) {}

Poison::Poison(string name ,int value, int newduration)
    : Object(name, "poison"), val(value), duration(newduration), curtime(0) {}

class Player; // Forward declaration
bool Poison::triggerEvent(Object* obj){
    Player* player = dynamic_cast<Player*>(obj);
    player->setPoisoned(true);
    player->setPoisonstate(*this);

    int finditem = player->findItem("rabbit");
    if(finditem == -1) finditem  = player->findItem("wild boar");
    if(finditem == -1) finditem = player->findItem("deer");
    if(finditem == -1) finditem = player->findItem("antidote");
    
    char option = 'b';
    cout << "What do you want to do? " << endl;
    cout << "a. I don't want to do anything. Just stay in poison state." << endl;
    if(player->findItem("milk") == -1) {
        cout << option << ". get the hint of milk for 30 coins" << endl;
        option++;
    } else {
        cout << option << ". use milk to detoxify" << endl;
        option++;
    }
    if(finditem != -1){
        cout  << option << ". provide an animal captured in animal forest in exchange of the antidose" << endl;
    }

    char ans;
    bool isValidInput = false;
    do{
        cout << "Your choice: ";
        cin >> ans;
        if(ans == 'a'){
            return true;
        } else if(ans == 'b'){
            if(player->getCoin() < 30){
                cout << "Sorry, you don't have enough coins" << endl;
            } else {
                player->setCoin(player->getCoin() - 30);
                if(player->findItem("milk") == -1) {
                    cout << "\033[1;34mThe milk is in the secret room. The key number for the room is the answer of Schrödinger question.\033[0m" << endl;
                } else {
                    player->setPoisoned(false);
                }
            } 
            isValidInput = true;
        } else if(ans == 'c' && finditem != -1) {
            vector<string> animals = {"rabbit", "wild boar", "deer"};
            int animal = -1;
            for(const string& animalName : animals) {
                int animalIndex = player->findItem(animalName);
                if(animalIndex != -1) {
                    animal = animalIndex;
                        break;
                }
            }
            if(animal != -1) {
                player->eraseItem(animal);
            }
            string itemname = "antidote";
            player->addItem(Item(itemname, 0, 0, 0, 0, 0, 0, false));
            player->setPoisoned(false);
            isValidInput = true;
        } else {
            cout << "##############################################" << endl;
            cout << "#        OOOOOPS!! Please Input Again.       #" << endl;
            cout << "##############################################" << endl;
        }
    }while(!isValidInput);
    return true;
}
bool Poison::addCurtime(){
    if(++curtime == duration) return true;
    return false;
}

int Poison::getVal() const {
    return val;
}

int Poison::getDuration() const {
    return duration;
}

int Poison::getCurtime() const {
    return curtime;
}


void Poison::setVal(int value) {
    val = value;
}

void Poison::setDuration(int d) {
    duration = d;
}

void Poison::setCurtime(int newcurtime){
    curtime = newcurtime;
}

