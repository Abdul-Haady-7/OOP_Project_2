#include <iostream>
#include "Date.h"

using namespace std;

Date::Date(int d, int m, int y) {
    day = d;
    month = m;
    year = y;
}

bool Date::isIn24(const Date& rightNow) const {
    if (this->year == rightNow.year && this->month == rightNow.month) {
        return (rightNow.day - this->day <= 1 && rightNow.day - this->day >= 0);
    }
    return false;
}

int Date::yearDiff(const Date& rightNow) const {
    return rightNow.year - this->year;
}

void Date::display() const {
    cout << day << "/" << month << "/" << year;
}