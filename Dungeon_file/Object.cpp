#include "Object.h"

Object::Object() {
    // Initialize name and tag to empty strings
    /*name = "";
    tag = "";*/
}

Object::Object(string newName, string newTag) : name(newName), tag(newTag){}

/* Getter and setter functions */
void Object::setName(string newName) {
    name = newName;
}

void Object::setTag(string newTag) {
    tag = newTag;
}

string Object::getName() {
    return name;
}

string Object::getTag() {
    return tag;
}