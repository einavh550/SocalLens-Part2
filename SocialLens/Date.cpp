#include "Date.h"
#include <cstdio>
#include <cstring>

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

char* Date::toString() const
{
    char buffer[32];
    std::snprintf(buffer, sizeof(buffer), "%02d/%02d/%04d", day, month, year);

    int length = static_cast<int>(std::strlen(buffer));
    char* result = new char[length + 1];
    std::memcpy(result, buffer, length + 1);
    return result;
}
