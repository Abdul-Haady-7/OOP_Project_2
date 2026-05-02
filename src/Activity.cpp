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
}