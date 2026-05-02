#pragma once
#include <iostream>
#include <string>
#include "Post.h"

using namespace std;

class Activity : public Post { 
private:
    int activityType; 
    string activityValue; 

public:
    Activity(string id, string desc, Date d, Object* auth, int t, string v); 
    void display() const override; 
};
