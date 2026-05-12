/* ==========================================================================
 * Class: Date
 * Type: Utility/Helper Class
 * Purpose: Manages date information for posts, memories, and the system clock.
 * It provides comparison functions needed to filter the Home Page 
 * (posts from the last 24 hours) and calculate how many years ago
 * a memory was originally posted.
 * ========================================================================== */

#include <iostream>
#include "Date.h"

using namespace std;

// Constructor: Initializes the date with day, month, and year values
Date::Date(int d, int m, int y) {
    day = d;
    month = m;
    year = y;
}

// Checks if this date is within 24 hours (1 day) of the provided 'rightNow' date
bool Date::isIn24(const Date& rightNow) const {
    // First ensures the year and month are exactly the same
    if (this->year == rightNow.year && this->month == rightNow.month) {
        // Returns true if the difference in days is 0 (same day) or 1 (previous day)
        return (rightNow.day - this->day <= 1 && rightNow.day - this->day >= 0);
    }
    return false; // Automatically false if the month or year differs
}

// Calculates how many years have passed between this date and 'rightNow'
int Date::yearDiff(const Date& rightNow) const {
    return rightNow.year - this->year; // Used to display "X Years Ago" for memories
}

// Prints the date to the console in DD/MM/YYYY format
void Date::display() const {
    cout << day << "/" << month << "/" << year;
}