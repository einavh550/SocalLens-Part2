#ifndef DATE_H
#define DATE_H

class Date
{
private:
    int day;
    int month;
    int year;

public:
    //constructors
    Date();
    Date(int d, int m, int y);
    //getters
    int getDay() const;
    int getMonth() const;
    int getYear() const;
    //setters
    void setDay(int d);
    void setMonth(int m);
    void setYear(int y);

    char* toString() const; //this function will be responsible
    //to allocate memory for a string and provide the date as a string for printing
};

#endif //DATE_H