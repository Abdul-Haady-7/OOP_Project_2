/* ==========================================================================
 * Class: Memory
 * Type: Derived Class (Inherits from Post)
 * Purpose: Represents a re-shared past post. It holds a pointer to the 
 * original post being shared and calculates the time difference. 
 * When displayed, it prints the sharer's new caption and then 
 * embeds the original post directly beneath it.
 * ========================================================================== */

#include <iostream>
#include <string>
#include "Memory.h"
#include "Post.h"
#include "Date.h"

using namespace std;

// Constructor: Initializes a Memory by passing data to base Post, and storing a pointer to the original post
Memory::Memory(string id, string desc, Date d, Object* author, Post* original) : Post(id, desc, d, author) {
    originalPost = original;
}

// Getter: Returns the pointer to the embedded original post
Post* Memory::getOriginalPost() const {
    return originalPost;
}

// Overrides Post display to format the memory header, then print the original embedded post
void Memory::display() const {
    cout << "~~~ ";
    author[0]->display();
    cout << " shared a memory ~~~ ...(";
    date.display();
    cout << ")" << endl;
    
    cout << "\"" << description << "\"" << endl;
    
    // Calculates how many years ago the original post was made relative to the memory's share date
    int years = originalPost->getDate()->yearDiff(this->date);
    cout << "\t\t\t\t\t(" << years << " Years Ago)" << endl;
    
    // Triggers the display function of the original post directly beneath the memory text
    originalPost->display();
}