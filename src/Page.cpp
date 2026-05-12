/* ==========================================================================
 * Class: Page
 * Type: Derived Class (Inherits from Object)
 * Purpose: Represents a business, brand, or public figure. Pages can author
 * posts and have a timeline of posts, but they do not have "friends".
 * Users can follow/like Pages to see Page posts on their Home feed.
 * ========================================================================== */

#include "Page.h"
#include "Post.h"

using namespace std;

// Constructor: Initializes Page and base Object, and sets up empty arrays
Page::Page(string id, string n) : Object(id) {
    this->name = n;
    this->postCount = 0;
    this->posts = nullptr; 
}

// Adds a Post pointer to the Page's dynamic timeline array
void Page::addPost(Post* p) {
    // Lazy initialization: allocates the array only when the first post is added
    if (posts == nullptr) {
        posts = new Post*[100]; 
        for(int i = 0; i < 100; i++) posts[i] = nullptr; // Nulls out the array for safety
    }
    
    // Inserts the post and increments count if under the hard limit
    if (postCount < 100) {
        posts[postCount++] = p;
    }
}

// Basic Getters for Page attributes
Post** Page::getPosts() const { return posts; }
int Page::getPostCount() const { return postCount; }
string Page::getName() const { return name; }

// Overrides Object display to just print the Page's Name
void Page::display() const {
    cout << name;
}

// Destructor: Frees the array holding the Post pointers (does not delete the posts themselves)
Page::~Page() {
    if (posts != nullptr) {
        delete[] posts;
    }
}