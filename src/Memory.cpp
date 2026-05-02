#include <iostream>
#include <string>
#include "Memory.h"
#include "Post.h"
#include "Date.h"

using namespace std;

Memory::Memory(string id, string desc, Date d, Object* author, Post* original) : Post(id, desc, d, author) {
    originalPost = original;
}

Post* Memory::getOriginalPost() const {
    return originalPost;
}

void Memory::display() const {
}