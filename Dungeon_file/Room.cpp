#include "Room.h"

// Default constructor
Room::Room()
    : upRoom(nullptr), downRoom(nullptr), leftRoom(nullptr), rightRoom(nullptr),
      isExit(false), index(-1){}

// Parameterized constructor
Room::Room(bool exit, int idx, vector<Object*> objs)
    : upRoom(nullptr), downRoom(nullptr), leftRoom(nullptr), rightRoom(nullptr),
      isExit(exit), index(idx), objects(objs) {}
      
// Function to pop out a specific object
bool Room::popObject(Object* obj) {
    for (auto it = objects.begin(); it != objects.end(); ++it) {
        if (*it == obj) {
            objects.erase(it);
            return true;
        }
    }
    return false; // Object not found
}

void Room::popBackObject() {
    objects.pop_back();
}

void Room::showWelcomeMessage() {
    switch (index)
    {
    case 0:
        cout << "Welcome to West Town" << endl;
        cout << "Let's draw lot! Please choose a number from 1 to 100: ";
        int num;
        while (!(std::cin >> num)) { // 檢查輸入是否是整數，如果不是，重複提示
            std::cout << "Invalid input. Please enter a valid number: ";
            std::cin.clear(); // 清除錯誤標誌
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 忽略錯誤輸入
        }
        break;
    case 2:
        cout << "Welcome to the Forest," << endl;
        cout << "whispers the breeze through the ancient trees." << endl;
        cout << "\033[1;35mbeware: your hunger will intensify every ten seconds,\033[0m " << endl;
        cout << "posing a constant challenge to your survival." << endl;
        break;
    case 3:
        cout << "Welcome to the Hotel! Prepare to embark on an adventure filled with secrets and surprises." << endl;
        cout << "Don't forget to explore the Dungeon to uncover the elusive map." << endl;
        break;
    case 4:
        imagefile.addFileName("zombie.txt");
        imagefile.printFile(0);
        break;
    case 5:
        /*cout << "You find out the exit of Dungeon!" << endl<< endl;
        cout << " ______   ______   .__   __.   _______ .______          ___   .___________. __    __   __          ___   .___________. __    ______   .__   __. " << endl;
        cout << "/      | /  __  \\  |  \\ |  |  /  _____||   _  \\        /   \\  |           ||  |  |  | |  |        /   \\  |           ||  |  /  __  \\  |  \\ |  | " << endl;
        cout << "|  ,----'|  |  |  | |   \\|  | |  |  __  |  |_)  |      /  ^  \\ `---|  |----`|  |  |  | |  |       /  ^  \\ `---|  |----`|  | |  |  |  | |   \\|  | " << endl;
        cout << "|  |     |  |  |  | |  . `  | |  | |_ | |      /      /  /_\\  \\    |  |     |  |  |  | |  |      /  /_\\  \\    |  |     |  | |  |  |  | |  . `  | " << endl;
        cout << "|  `----.|  `--'  | |  |\\   | |  |__| | |  |\\  \\----./  _____  \\   |  |     |  `--'  | |  `----./  _____  \\   |  |     |  | |  `--'  | |  |\\   | " << endl;
        cout << "\\______| \\______/  |__| \\__|  \\______| | _| `._____/__/     \\__\\  |__|      \\______/  |_______/__/     \\__\\  |__|     |__| \\______/  |__| \\__| " << endl;*/
        
        break;
    case 6:
        cout << "Step into the scorching Desert." << endl;
        cout << "\033[1;35mbeware: your hunger and thirst will intensify every ten seconds,\033[0m " << endl;
        cout << "posing a constant challenge to your survival." << endl;
        cout << "                /||\\          " << endl;
        cout << "                ||||          " << endl;
        cout << "                ||||          " << endl;
        cout << "                |||| /|\\      " << endl;
        cout << "           /|\\  |||| |||      " << endl;
        cout << "           |||  |||| |||       " << endl;
        cout << "           |||  |||| |||       " << endl;
        cout << "           |||  |||| d||       " << endl;
        cout << "           |||  |||||||/       " << endl;
        cout << "           ||b._||||~~'        " << endl;
        cout << "           \\||||||||          " << endl;
        cout << "            `~~~||||          " << endl;
        cout << "                ||||          " << endl;
        cout << "                ||||          " << endl;
        cout << "~~~~~~~~~~~~~~~~||||~~~~~~~~~~~~~~" << endl;
        cout << "  \\/..__..--  . |||| \\/  .  .." << endl;
        cout << "\\/         \\/ \\/    \\/" << endl;
        cout << "        .  \\/              \\/    ." << endl;
        cout << ". \\/             .   \\/     ." << endl;
        cout << "   __...--..__..__       .     \\/" << endl;
        cout << "\\/  .   .    \\/     \\/    __..--.." << endl;
        cout << endl;
        break;
    case 7:
        cout << "You come to the start room." << endl;
        break;
    default:
        break;
    }
}

void Room::addObject(Object* obj){
    objects.push_back(obj);
}
// Setters
void Room::setUpRoom(Room* room) {
    upRoom = room;
}

void Room::setDownRoom(Room* room) {
    downRoom = room;
}

void Room::setLeftRoom(Room* room) {
    leftRoom = room;
}

void Room::setRightRoom(Room* room) {
    rightRoom = room;
}

void Room::setIsExit(bool exit) {
    isExit = exit;
}

void Room::setIndex(int idx) {
    index = idx;
}

void Room::setObjects(vector<Object*> objs) {
    objects = objs;
}

// Getters
bool Room::getIsExit() {
    return isExit;
}

int Room::getIndex() {
    return index;
}

vector<Object*> Room::getObjects() {
    return objects;
}

Room* Room::getUpRoom() {
    return upRoom;
}

Room* Room::getDownRoom() {
    return downRoom;
}

Room* Room::getLeftRoom() {
    return leftRoom;
}

Room* Room::getRightRoom() {
    return rightRoom;
}