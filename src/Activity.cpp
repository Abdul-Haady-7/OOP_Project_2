#include <iostream>
#include <string>
#include "Activity.h"
#include "Post.h"
#include "Date.h"

using namespace std;

Activity::Activity(string id, string desc, Date d, Object* auth, int t, string v) : Post(id, desc, d, auth) {
    activityType = t;
    activityValue = v;
}

void Activity::display() const {
    cout << "--- ";
    author[0]->display();
    cout << " is ";
    
    if (activityType == 1) cout << "feeling ";
    else if (activityType == 2) cout << "thinking about ";
    else if (activityType == 3) cout << "making ";
    else if (activityType == 4) cout << "Celebrating ";
    
    cout << activityValue << endl;
    cout << "     \"" << description << "\" ... (";
    date.display();
    cout << ")" << endl;

    for (int i = 0; i < commentsCount; i++) {
        comments[i]->display();
    }
}