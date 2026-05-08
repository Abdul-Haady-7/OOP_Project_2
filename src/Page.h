#pragma once
#include <iostream>
#include <string>
#include "Object.h"

using namespace std;


class Post;

class Page : public Object {
private:
    string name;
    Post** posts; 
    int postCount; 

public:
    Page(string id, string n);

    void addPost(Post* p);

    Post** getPosts() const;
    int getPostCount() const;
    string getName() const;

    void display() const override;

    ~Page();
};