#pragma once
#include <iostream>
#include "User.h";
#include "Page.h";
#include "Post.h";
#include "Comment.h";
#include "Date.h";


using namespace std;

class SocialNetworkApp{
private:
    User** users;
    int userCount;
    Page** pages;
    int pageCount;
    Post** posts;
    int postCount;
    Comment** comments;
    int commentCount;
    User* currentUser;
    Date theDate;

    //Private Methods
    User* findUser();
    Page* findPage();
    Post* findPost();
public:
    void loadData();
    void run();
    void setUser();
    void viewHome();
    void likePost();
    void viewLikedList();
    void commentOnPost();
    void viewPost();
    void seeMemory();
    void shareMemory();
    void viewProfile();
    void viewFriendList();
    void viewPage();
    ~SocialNetworkApp();
};