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
    cout << "~~~ ";
    author[0]->display();
    cout << " shared a memory ~~~ ...(";
    date.display();
    cout << ")" << endl;
    
    cout << "\"" << description << "\"" << endl;
    
    int years = originalPost->getDate()->yearDiff(this->date);
    cout << "\t\t\t\t\t(" << years << " Years Ago)" << endl;
    
    originalPost->display();
}