#ifndef DATE_H
#define DATE_H

#include <ostream>

class Date
{
private:
    int day;
    int month;
    int year;

public:
    Date();
    Date(int d, int m, int y);

    int getDay() const;
    int getMonth() const;
    int getYear() const;

    void setDay(int d);
    void setMonth(int m);
    void setYear(int y);

    friend std::ostream& operator<<(std::ostream& os, const Date& date);
};

#endif
