#pragma once
#include <iostream>
#include "Page.h"
using namespace std;

class User{
private:
    string name;
    User** friends;
    int friendsCount;
    Page** likedPages;
    int likedPagesCount;
public:
    User(string n);
    void addFriend();
    void addLikedPage();
    User** getFriends() const;
    int getFriendsCount() const;
    Page** getLikedPages() const;
    int getLikedPagesCount() const;
    string getName() const;
    void display() const;
    ~User();
};