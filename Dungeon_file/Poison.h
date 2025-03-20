#ifndef POISON_H_INCLUDED
#define POISON_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "Object.h"
#include "Item.h"

using namespace std;
class Item;
class Poison : public Object
{
private:
    int val;
    int duration;
    int curtime;
public:
    // Constructors
    Poison();
    Poison(string ,int ,int);
    bool triggerEvent(Object*);
    bool addCurtime();
    // Getters
    int getVal() const;
    int getDuration() const;
    int getCurtime() const;

    // Setters
    void setVal(int);
    void setDuration(int);
    void setCurtime(int);
};

#endif // POISON_H_INCLUDED
