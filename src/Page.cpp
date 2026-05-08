#include "Page.h"
#include "Post.h"

using namespace std;

Page::Page(string id, string n) : Object(id) {
    this->name = n;
    this->postCount = 0;
    
    this->posts = nullptr; 
}

void Page::addPost(Post* p) {
    
    if (posts == nullptr) {
        posts = new Post*[100]; 
        for(int i = 0; i < 100; i++) posts[i] = nullptr;
    }
    
    if (postCount < 100) {
        posts[postCount++] = p;
    }
}

Post** Page::getPosts() const { return posts; }
int Page::getPostCount() const { return postCount; }
string Page::getName() const { return name; }

void Page::display() const {
    cout << name;
}

Page::~Page() {
    if (posts != nullptr) {
        delete[] posts;
    }
}