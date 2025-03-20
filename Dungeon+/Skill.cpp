#include "Skill.h"

Skill::Skill() : Object(), health(0), attack(0), defense(0), cost(0) {}

Skill::Skill(string name, int skillHealth, int skillAttack, int skillDefense, int skillCost) : 
Object(name, "skill"),  health(skillHealth), attack(skillAttack), defense(skillDefense), cost(skillCost) {}

bool Skill::triggerEvent(Object* obj) {
    // 檢查參數是否是 Player 對象
    Player* player = dynamic_cast<Player*>(obj);
    if (player) {
        // 將技能效果應用到玩家身上，例如增加/減少玩家的屬性值、狀態等
        //player->increaseStates(health, attack, defense);
        cout << "You used " << getName() << ". ";
        cout << "Health: +" << health << ", Attack: +" << attack << ", Defense: +" << defense << endl;
        return true; // 返回 true 表示事件處理成功
    } else {
        cout << "Error: Invalid object type!" << endl;
        return false; // 返回 false 表示事件處理失敗
    }

}

void Skill::changeEnemyAttack(double ratio){
    attack = attack*ratio;
}

void Skill::changeEnemyDefense(double ratio){
    defense = defense*ratio;
}

bool Skill::changeEnemyPoisonedorNot(double probablity){ 
    srand(time(NULL));
    probablity *= 1000;
    int random = rand() % 1000 + 1;
    if(0 < random && random <= probablity) {
        return true;
    }
    return false;
}

// getter 和 setter 函数的定义
string Skill::getScript() {
    return script;
}

void Skill::setScript(string skillScript) {
    script = skillScript;
}

void Skill::setHealth(int skillHealth) {
    health = skillHealth;
}

int Skill::getHealth() {
    return health;
}

void Skill::setAttack(int skillAttack) {
    attack = skillAttack;
}

int Skill::getAttack() {
    return attack;
}

void Skill::setDefense(int skillDefense) {
    defense = skillDefense;
}

int Skill::getDefense() {
    return defense;
}

void Skill::setCost(int skillCost) {
    cost = skillCost;
}

int Skill::getCost() {
    return cost;
}

void Skill::setHunger(int newhunger) {
    hunger  = newhunger;
}
