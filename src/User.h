#pragma once
#include <iostream>
#include <string>
#include "Object.h"

using namespace std;

class Page;
class Post;

class User : public Object {
private:
    string name;
    
    User** friends;
    int friendsCount;
    
    Page** likedPages;
    int likedPagesCount;
    
    Post** posts; 
    int postCount;

public:
    User(string id, string n);

    void addFriends(User* u);
    void addLikedPages(Page* p);
    void addPosts(Post* p);

    User** getFriends() const;
    int getFriendsCount() const;
    Page** getLikedPages() const;
    int getLikedPagesCount() const;
    string getName() const;
    Post** getPosts() const;
    int getPostCount() const;

    void display() const override;

    ~User();
};