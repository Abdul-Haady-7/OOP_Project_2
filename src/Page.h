#pragma once
#include <iostream>
#include "Post.h"


using namespace std;

class Page : {
private:
    string name;
    Post** postss;
    int postCount; 
public:
    page();
    void addPost();
    Post** getPosts();
    string getName();
    void display() const;
    ~page();

};

