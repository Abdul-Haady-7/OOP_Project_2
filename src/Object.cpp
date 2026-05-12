/* ==========================================================================
 * Class: Object
 * Type: Abstract Base Class
 * Purpose: Serves as the fundamental building block of the social network. 
 * Users, Pages, and Posts all inherit from this class. It provides 
 * a universal ID property and a pure virtual display() method, 
 * allowing the app to store different entities in the same arrays 
 * and dynamically call the correct display format.
 * ========================================================================== */

#include <iostream>
#include <string>
#include "Object.h"

using namespace std;

// Constructor: Initializes the base object with a unique ID
Object::Object(string id) {
    this->id = id;
}

// Getter: Returns the unique ID of the object
string Object::getID() const {
    return id;
}

// Virtual Destructor: Ensures derived classes clean up their memory properly
Object::~Object() {
    // Empty because Object itself doesn't allocate dynamic memory
}