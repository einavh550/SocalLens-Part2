#include "Date.h"
#include <cstdio>
#include <cstring>

// Default date: 1/1/2000. A default constructor lets other classes (e.g. Campaign)
// hold a Date member without always supplying one explicitly.
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

// Allocates a new C-string on the heap holding the date as "DD/MM/YYYY".
// The caller is responsible for releasing it with delete[].
char* Date::toString() const
{
    char buffer[32];
    // std::snprintf is bounded, so it can never overflow the buffer.
    std::snprintf(buffer, sizeof(buffer), "%02d/%02d/%04d", day, month, year);

    int length = static_cast<int>(std::strlen(buffer));
    char* result = new char[length + 1];
    std::strcpy(result, buffer);
    return result;
}
