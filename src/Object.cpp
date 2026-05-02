#include <iostream>
#include <string>
#include "Object.h"

using namespace std;

Object::Object(string id) {
    this->id = id;
}

string Object::getID() const {
    return id;
}

Object::~Object() {
}