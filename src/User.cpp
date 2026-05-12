/* ==========================================================================
 * Class: User
 * Type: Derived Class (Inherits from Object)
 * Purpose: Represents a physical person using the application. It manages 
 * pointers connecting the user to their friends, the Pages they 
 * have liked, and a timeline of the Posts they have created.
 * ========================================================================== */

#include "User.h"
#include "Page.h"
#include "Post.h"

using namespace std;

// Constructor: Initializes User and base Object, and sets up empty tracking arrays
User::User(string id, string n) : Object(id) {
    this->name = n;
    this->friendsCount = 0;
    this->likedPagesCount = 0;
    this->postCount = 0;

    this->friends = nullptr;
    this->likedPages = nullptr;
    this->posts = nullptr;
}

// Adds a pointer to another User to represent a friend connection
void User::addFriends(User* u) {
    // Lazy initialization of the dynamic array
    if (friends == nullptr) {
        friends = new User*[10]; 
        for(int i = 0; i < 10; i++) friends[i] = nullptr;
    }
    
    if (friendsCount < 10) {
        friends[friendsCount++] = u; // Inserts and increments count in one line
    }
}

// Adds a pointer to a Page this user liked
void User::addLikedPages(Page* p) {
    if (likedPages == nullptr) {
        likedPages = new Page*[10];
        for(int i = 0; i < 10; i++) likedPages[i] = nullptr;
    }
    
    if (likedPagesCount < 10) {
        likedPages[likedPagesCount++] = p;
    }
}

// Adds a pointer to a Post created by this user to their timeline
void User::addPosts(Post* p) {
    if (posts == nullptr) {
        posts = new Post*[10];
        for(int i = 0; i < 10; i++) posts[i] = nullptr;
    }
    
    if (postCount < 10) {
        posts[postCount++] = p;
    }
}

// Basic Getters for User arrays and attributes
User** User::getFriends() const { return friends; }
int User::getFriendsCount() const { return friendsCount; }
Page** User::getLikedPages() const { return likedPages; }
int User::getLikedPagesCount() const { return likedPagesCount; }
string User::getName() const { return name; }
Post** User::getPosts() const { return posts; }
int User::getPostCount() const { return postCount; }

// Overrides Object display to just print the User's Name
void User::display() const {
    cout << name;
}

// Destructor: Frees the pointer arrays (does not delete the actual friends/pages/posts)
User::~User() {
    if (friends != nullptr) delete[] friends;
    if (likedPages != nullptr) delete[] likedPages;
    if (posts != nullptr) delete[] posts;
}