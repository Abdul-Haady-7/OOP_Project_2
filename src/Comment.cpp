/* ==========================================================================
 * Class: Comment
 * Type: Data Class
 * Purpose: Represents a single comment on a post. It links an author 
 * (either a User or a Page, stored as an Object pointer) to a 
 * specific string of text. Posts manage collections of these.
 * ========================================================================== */

#include <iostream>
#include <string>
#include "Comment.h"
#include "Object.h"

using namespace std;

// Constructor: Initializes a comment with an ID, the author pointer, and text
Comment::Comment(string id, Object* auth, string t) {
    this->id = id;
    author = auth;
    text = t;
}

// Prints the comment indented, with the author's name and text
void Comment::display() const {
    cout << "\t\t\t\t\t";
    author->display(); // Polymorphic call: prints Page name or User name
    cout << " wrote: \"" << text << "\"" << endl;
}