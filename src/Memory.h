#pragma once
#include <iostream>
#include <string>
#include "Post.h"

using namespace std;

class Memory : public Post {
private:
    Post* originalPost;

public:
    Memory(string id, string desc, Date d, Object* author, Post* original);
    Post* getOriginalPost() const; 
    void display() const override; 
};