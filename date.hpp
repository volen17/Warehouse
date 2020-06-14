#include <fstream>
#pragma once

class Date
{
public:
    Date();
    Date(int, int, int);
    Date(char *);
    Date(const Date &);
    Date &operator=(const Date &);

    void set_year(short);
    void set_month(short);
    void set_day(short);

    short get_year() const;
    short get_month() const;
    short get_day() const;

    friend std::istream &operator>>(std::istream &, Date &);       // in ISO 8601
    friend std::ostream &operator<<(std::ostream &, const Date &); //in ISO 8601

    bool operator<=(const Date &) const;
    bool operator>(const Date &) const;
    bool operator>=(const Date &) const;

    bool isLeap();
    bool isValid();

private:
    short year;
    short day;
    short month;
};