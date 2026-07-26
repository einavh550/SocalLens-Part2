#include "Date.h"

Date::Date()
    : day(1), month(1), year(2000)
{
}

Date::Date(int d, int m, int y)
    : day(d), month(m), year(y)
{
}

int Date::getDay() const
{
    return day;
}

int Date::getMonth() const
{
    return month;
}

int Date::getYear() const
{
    return year;
}

void Date::setDay(int d)
{
    day = d;
}

void Date::setMonth(int m)
{
    month = m;
}

void Date::setYear(int y)
{
    year = y;
}

std::ostream& operator<<(std::ostream& os, const Date& date)
{
    if (date.day < 10)
        os << '0';
    os << date.day << '/';

    if (date.month < 10)
        os << '0';
    os << date.month << '/';

    if (date.year < 1000)
        os << '0';
    if (date.year < 100)
        os << '0';
    if (date.year < 10)
        os << '0';
    os << date.year;

    return os;
}
