#include "Environment.h"


Environment::Environment() {
    // 使用 GameCharacter 的默認構造函數來初始化屬性
}

Environment::Environment(string envName, string envScript, vector<Item> envCommodity, vector<NPC> envnpcs, vector<Monster> envmonsters,int hp, int mp, int attack, int defense, int envhunger, int envthirst) : 
    GameCharacter(envName, "environment", 0, hp, 0, mp, attack, defense, envhunger, envthirst), script(envScript), commodity(envCommodity), npcs(envnpcs) ,monsters(envmonsters){}

/*void Environment::listCommodity() {
    cout << "Items available for sale:" << endl;
    for (Item item : commodity) {
        cout << "Name: " << item.getName() << ", Health: " << item.getHealth() << ", Attack: " << item.getAttack() << ", Defense: " << item.getDefense() << endl;
    }
}*/

void timerFunc(atomic<bool>& stopFlag, Player* player, string& name) {
    auto startTime = chrono::steady_clock::now(); // 紀錄開始時間

    while (!stopFlag) {
        this_thread::sleep_for(chrono::seconds(1)); // 等待一秒鐘
        auto endTime = chrono::steady_clock::now(); // 計錄現在時間
        auto duration = chrono::duration_cast<chrono::seconds>(endTime - startTime); // 計算經過的時間

        if(duration.count() != 0 && duration.count() % 10 == 0) {
            cout << endl <<"\033[1;34m10 seconds have passed. And...\033[0m" << endl;
            if(name == "oasis") {
                player->increaseStates(0, 0, 0, 0, 0 , 4);
                cout << "Thirst increase to: " << player->getCurrentThirst() << endl;
            } else if(name == "sandstorm") {
                player->increaseStates(0, 0, 0, 0, 5, 10);
                cout << "Hunger increase to : " << player->getCurrentHunger() << endl;
                cout << "Thirst increase to: " << player->getCurrentThirst() << endl;
            } else if(name == "magic forest" || name == "animal forest") {
                player->increaseStates(0, 0, 0, 0, 5, 0);
                cout << "Hunger increase to : " << player->getCurrentHunger() << endl;
            } else if(name == "poisonstatus") {
                player->increaseStates(0, 0, 0, 0, 0 , 10);
                cout << "Thirst increase to: " << player->getCurrentThirst() << endl;
            } else if(name == "stuck" || name == "mummy swamp") {
                player->increaseStates(0, 0, 0, 0, 10 , 0);
                cout << "Thirst increase to: " << player->getCurrentHunger() << endl;
            } 
            
            if(player->getCurrentHealth() <= 0){
                stopFlag = true;
                break;
            } 
        }
        if(name ==  "sandstorm") {
            if (duration.count() >= 30) { 
                stopFlag = true;
                cout << "Congradulation, you survive. " << endl;
                cout << "Press any buttom to continue" << endl;
            }
        }
    }
}
bool Environment::triggerEvent(Object* obj) {

    Player* player = dynamic_cast<Player*>(obj);
    vector<Item> items = player->getInventory();
    cout << script << endl;
    string name = getName();
    atomic<bool> stopFlag(false); 
    thread timerThread(timerFunc, ref(stopFlag),ref(player),ref(name));
    if(getName() == "sandstorm") {
        //還有一種情況是已經有 compass 還要處理
        cout << endl << "Hey " << player->getName() << ", there is a " << commodity[0].getName() << endl;
        cout << "\033[1;32mDo you want to use compass? (y / n)\033[0m" << endl;
        commodity[0].listCommodity();
        char ans;
        cout << "Your choice: ";
        cin >> ans;
        if(ans == 'y') {
            if(player->findItem("compass") != -1){
                cout << "You've got this item." << endl;
                cout << "Congradulation, you go ouside the sandstorm" << endl;
                stopFlag = true;
            }else if(player->getCoin() >= commodity[0].getCoin()) {
                player->setCoin(player->getCoin() - commodity[0].getCoin());
                if(!commodity[0].getOnceUse()) {
                    player->addItem(commodity[0]);
                    commodity.erase(commodity.begin() + (0));
                }
                cout << "Congradulation, you go ouside the sandstorm" << endl;
                stopFlag = true;
            } else {
                cout << "OOPS! You don't have enough money" << endl;
                cout << "Sorry, you should wait for thirty seconds." << endl;
                char c;
                while((cin >> c)){
                    if(stopFlag) break;
                }
            } 
        } else {
            cout << "Sorry, you should wait for thirty seconds." << endl;
            char c;
            while((cin >> c)){
                if(stopFlag) break;
            }
        }
        if(player->getCurrentHealth() <= 0){
            return false;
        } 
    } else if(getName() == "oasis") {
        string oasisitemname = "coconut";
        npcs[0].addCommodity(Item(oasisitemname, 0, 0, 0, 0, 20, 0, true)); //coconut
        npcs[0].triggerEvent(player);
        stopFlag = true;
    } else if(getName() == "magic forest") {
        if(!monsters.empty()){
            if(!monsters[0].triggerEvent(player)) {
                stopFlag = true;
                timerThread.join();
                return false;
            }
            //monster only appear one time
            monsters.pop_back();
        } else {
            cout << "You have killed the tigers." << endl;
        }
        commodity[0].triggerEvent(player);
        stopFlag = true;
    } else if(getName() == "animal forest") {
        //implement
        cout << "\033[1;35mWhich one do you want to capture?\033[0m " << endl;
        char option = 'a';
        for (Monster monster : monsters) {
            cout << option << ". " << monster.getName() << endl;
            option++;
        }
        cout << option << ". I don't want to do anything" << endl;
        
        bool isValidInput = false;
        char c;
        do{
            cout << "Your choice: ";
            cin >> c;
            size_t idx = (int)(c - 'a');
            if(idx < monsters.size()) {
                if(!monsters[idx].triggerEvent(player)) {
                    stopFlag = true;
                    timerThread.join();
                    return false;
                }
                cout << "Catch the " << monsters[idx].getName() << endl;
                player->addItem(commodity[idx]);
                monsters.erase(monsters.begin() + idx);
                stopFlag = true;
                isValidInput = true;
            }else if(idx == monsters.size()) {
                cout << "Go ouside the room. " << endl;
                stopFlag = true;
                isValidInput = true;
            } else {
                cout << "##############################################" << endl;
                cout << "#        OOOOOPS!! Please Input Again.       #" << endl;
                cout << "##############################################" << endl;
            }
        }while(!isValidInput);
    } else if(getName() == "poisonstatus") {
       
        cout << "You've fallen into my clutches, haven't you? Well, well... Seems like you're in quite the predicament." << endl;
        cout << "But fear not, my friend. If you're willing to strike a deal with me," << endl;
        cout << "I can offer you the antidote to your ailment and a chance to escape." << endl;
       
        if(!player->getPoisoned())
            poison.triggerEvent(player);
        stopFlag = true;
    } else if(getName() == "stuck"){
        cout << "\033[1;32mEnter space to start the timer.\033[0m" << endl;
        // 等待玩家按下空格键
        while (getchar() != ' ') {
            // 如果没有按下空格键就一直等待
        }
        int fd = STDIN_FILENO;
        struct pollfd fds[1];
        fds[0].fd = fd;
        fds[0].events = POLLIN;

        std::cout << "\033[1;32mQuick! Press space key within 2 seconds...\033[0m" << endl;

        int ret = poll(fds, 1, 2000); // 等待兩秒

        if (ret == -1) {
            std::cerr << "poll() failed!\n";
            return false;
        } else if (ret == 0) {
            
        } else {
            if (fds[0].revents & POLLIN) {
                // 空白鍵被按下
                char buf[2];
                if (read(fd, buf, sizeof(buf)) == -1) {
                    std::cerr << "read() failed!\n";
                }   
                if (buf[0] == ' ') {
                    cout << "Congratulations! You survive in the swamp." << endl;
                    cout << "You got 10 coins" << endl;
                    player->setCoin(player->getCoin() + 10);
                    stopFlag = true;
                    timerThread.join();
                    return true;
                } 
            }
        }
        cout << "Sorry, you failed to flee. Try another way to flee." << endl; 
        cout << "health minus 10, hunger increase 20" << endl;
        player->increaseStates(-10, 0, 0, 0, 20, 0);
        stopFlag = true;
        timerThread.join();
        return false;
    } else if(getName() == "mummy swamp"){
        if(!monsters[0].triggerEvent(player)) {
            cout << "OOPS!!!" << endl;
            stopFlag = true;
            timerThread.join();
            return false;
        }
        //monster only appear one time
        monsters.pop_back();
        stopFlag = true;
    }
    timerThread.join();
    return true; 
}

void Environment::setScript(string envScript) {
    script = envScript;
}

void Environment::setCommodity(vector<Item> envCommodity) {
    commodity = envCommodity;
}

void Environment::setPoison(Poison newpoison){
    poison = newpoison;
}

string Environment::getScript() {
    return script;
}

vector<Item> Environment::getCommodity() {
    return commodity;
}

Poison Environment::getPoison(){
    return poison;
}