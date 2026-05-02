#pragma once
#include <iostream>
#include <string>
#include "Object.h"

using namespace std;

// Forward declarations

class Page;
class Post;

class User : public Object {
private:
    string name;
    
    // Arrays of pointers 
    User** friends;
    int friendsCount;
    
    Page** likedPages;
    int likedPagesCount;
    
    Post** posts; 
    int postCount;

public:
    // Constructor
    User(string id, string n);

    // Methods to populate the arrays
    void addFriend(User* u);
    void addLikedPage(Page* p);
    void addPost(Post* p);

    // Getters
    User** getFriends() const;
    int getFriendsCount() const;
    Page** getLikedPages() const;
    int getLikedPagesCount() const;
    string getName() const;

    // Overriding the pure virtual function from Object
    void display() const override;

    // Destructor
    ~User();
};