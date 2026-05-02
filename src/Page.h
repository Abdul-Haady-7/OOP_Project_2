#pragma once
#include <iostream>
#include <string>
#include "Object.h"

using namespace std;

// Forward declaration 

class Post;

class Page : public Object {
private:
    string name;
    Post** posts; 
    int postCount; 

public:
    // Constructor needs ID for the Object base class
    Page(string id, string n);

    // Method
    void addPost(Post* p);

    // Getters
    Post** getPosts() const;
    int getPostCount() const;
    string getName() const;

    // Overriding the pure virtual function from Object
    void display() const override;

    // Destructor
    ~Page();
};