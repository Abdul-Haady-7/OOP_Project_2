#pragma once
#include <iostream>
#include <string>
#include "Object.h"

using namespace std;

class Comment {
private:
    string id; 
    string text;
    Object* author; 

public:
    Comment(string id, Object* auth, string t);
    void display() const;
};
