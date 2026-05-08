#include <iostream>
#include <string>
#include "Comment.h"
#include "Object.h"

using namespace std;

Comment::Comment(string id, Object* auth, string t) {
    this->id = id;
    author = auth;
    text = t;
}

void Comment::display() const {
    cout << "\t\t\t\t\t";
    author->display();
    cout << " wrote: \"" << text << "\"" << endl;
}