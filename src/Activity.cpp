/* ==========================================================================
 * Class: Activity
 * Type: Derived Class (Inherits from Post)
 * Purpose: Represents a specialized type of Post where the user shares an 
 * action or feeling (e.g., "thinking about", "celebrating"). It 
 * overrides the default Post display to format the activity verbs 
 * correctly before showing the standard post description.
 * ========================================================================== */

#include <iostream>
#include <string>
#include "Activity.h"
#include "Post.h"
#include "Date.h"

using namespace std;

// Constructor: Initializes an Activity by calling the base Post constructor, then setting activity specifics
Activity::Activity(string id, string desc, Date d, Object* auth, int t, string v) : Post(id, desc, d, auth) {
    activityType = t; // Integer representing feeling, thinking, making, or celebrating
    activityValue = v; // The string detail (e.g., "excited", "a birthday")
}

// Overrides Post display to print the specific Activity formatting before the description
void Activity::display() const {
    cout << "--- ";
    author[0]->display();
    cout << " is ";
    
    // Translates the integer type into the correct readable verb
    if (activityType == 1) cout << "feeling ";
    else if (activityType == 2) cout << "thinking about ";
    else if (activityType == 3) cout << "making ";
    else if (activityType == 4) cout << "Celebrating ";
    
    cout << activityValue << endl;
    cout << "     \"" << description << "\" ... (";
    date.display();
    cout << ")" << endl;

    // Loops through and prints all comments attached to this specific activity
    for (int i = 0; i < commentsCount; i++) {
        comments[i]->display();
    }
}