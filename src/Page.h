#pragma once
#include <iostream>

using namespace std;

class page{
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

