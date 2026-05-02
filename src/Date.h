#pragma once
#include <iostream>

using namespace std;


class Date{

private:
    int day;
    int month;
    int year;

public:
    Date(int d, int m, int y){};
    
    bool isIn24(const Date& rightNow) const;
    int yearDiff(const Date& rightNow) const;

    void display() const;

};