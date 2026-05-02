#pragma once

#include <iostream>
using namespace std;

class Object{

private:
    string id;

public:
    Object(string id){};

    string getID() const{};
    virtual void display() const= 0;

    virtual ~Object(){};
};


