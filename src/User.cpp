#include "User.h"
#include "Page.h"
#include "Post.h"

using namespace std;

// Constructor
User::User(string id, string n) : Object(id) {
    this->name = n;
    this->friendsCount = 0;
    this->likedPagesCount = 0;
    this->postCount = 0;

    this->friends = nullptr;
    this->likedPages = nullptr;
    this->posts = nullptr;
}

void User::addFriends(User* u) {
    
    if (friends == nullptr) {
        friends = new User*[10]; // Arbitrary max size 
        for(int i = 0; i < 10; i++) friends[i] = nullptr;
    }
    
    if (friendsCount < 10) {
        friends[friendsCount++] = u;
    }
}

void User::addLikedPages(Page* p) {
    if (likedPages == nullptr) {
        likedPages = new Page*[10];
        for(int i = 0; i < 10; i++) likedPages[i] = nullptr;
    }
    
    if (likedPagesCount < 10) {
        likedPages[likedPagesCount++] = p;
    }
}

void User::addPosts(Post* p) {
    if (posts == nullptr) {
        posts = new Post*[10];
        for(int i = 0; i < 10; i++) posts[i] = nullptr;
    }
    
    if (postCount < 10) {
        posts[postCount++] = p;
    }
}

// Getters
User** User::getFriends() const { return friends; }
int User::getFriendsCount() const { return friendsCount; }
Page** User::getLikedPages() const { return likedPages; }
int User::getLikedPagesCount() const { return likedPagesCount; }
string User::getName() const { return name; }
Post** User::getPosts() const { return posts; }
int User::getPostCount() const { return postCount; }

void User::display() const {
    cout << name;
}

// Destructor
User::~User() {
    if (friends != nullptr) delete[] friends;
    if (likedPages != nullptr) delete[] likedPages;
    if (posts != nullptr) delete[] posts;
}