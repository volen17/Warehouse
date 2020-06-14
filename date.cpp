#include "date.hpp"
#include <iostream>
#include <cstring>

///Contructors / operator= / operator>> / operator<< /operator<= / operator> / operator>=:
///
Date::Date()
{
    year = 0;
    month = 0;
    day = 0;
}

Date::Date(int year, int month, int day)
{
    this->year = year;
    this->month = month;
    this->day = day;
}

Date::Date(char *date)
{
    if (date[7] == '-' && strlen(date) == 10)
    {
        this->year = ((((short)date[0] - 48) * 1000) + (((short)date[1] - 48) * 100) + (((short)date[2] - 48) * 10) + ((short)date[3] - 48));
        this->month = ((((short)date[5] - 48) * 10) + ((short)date[6] - 48));
        this->day = ((((short)date[8] - 48) * 10) + ((short)date[9] - 48));
    }
    if (date[7] == '-' && strlen(date) == 9)
    {
        this->year = ((((short)date[0] - 48) * 1000) + (((short)date[1] - 48) * 100) + (((short)date[2] - 48) * 10) + ((short)date[3] - 48));
        this->month = ((((short)date[5] - 48) * 10) + ((short)date[6] - 48));
        this->day = ((short)date[8] - 48);
    }
    if (date[6] == '-' && strlen(date) == 9)
    {
        this->year = ((((short)date[0] - 48) * 1000) + (((short)date[1] - 48) * 100) + (((short)date[2] - 48) * 10) + ((short)date[3] - 48));
        this->month = ((short)date[5] - 48);
        this->day = ((((short)date[7] - 48) * 10) + ((short)date[8] - 48));
    }
    if (date[6] == '-' && strlen(date) == 8)
    {
        this->year = ((((short)date[0] - 48) * 1000) + (((short)date[1] - 48) * 100) + (((short)date[2] - 48) * 10) + ((short)date[3] - 48));
        this->month = ((short)date[5] - 48);
        this->day = ((short)date[7] - 48);
    }
}

Date::Date(const Date &other)
{
    year = other.year;
    month = other.month;
    day = other.day;
}

Date &Date::operator=(const Date &other)
{
    if (this != &other)
    {
        year = other.year;
        month = other.month;
        day = other.day;
    }
    return *this;
}

std::istream &operator>>(std::istream &in, Date &d)
{
    short year, month, day;
    char ch1, ch2;
    if (in >> year >> ch1 >> month >> ch2 >> day)
    {
        if (ch1 == '-' && ch2 == '-')
            d = Date(year, month, day);
        else
            in.setstate(std::ios::failbit);
    }
    return in;
}

std::ostream &operator<<(std::ostream &out, const Date &date)
{
    if (date.year < 10)
    {
        out << "000" << date.year << "-";
    }
    else if (date.year < 100)
    {
        out << "00" << date.year << "-";
    }
    else if (date.year < 1000)
    {
        out << "0" << date.year << "-";
    }
    else
    {
        out << date.year << "-";
    }
    if (date.month <= 9)
    {
        out << "0" << date.month << "-";
    }
    else
    {
        out << date.month << "-";
    }
    if (date.day <= 9)
    {
        out << "0" << date.day;
    }
    else
    {
        out << date.day;
    }
    return out;
}

bool Date::operator<=(const Date &date) const
{
    if (year < date.year)
    {
        return true;
    }
    else if (year == date.year)
    {
        if (month < date.month)
        {
            return true;
        }
        else if (month == date.month)
        {
            if (day <= date.day)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool Date::operator>(const Date &date) const
{
    if (year > date.year)
    {
        return true;
    }
    else if (year == date.year)
    {
        if (month > date.month)
        {
            return true;
        }
        else if (month == date.month)
        {
            if (day > date.day)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool Date::operator>=(const Date &date) const
{
    if (year > date.year)
    {
        return true;
    }
    else if (year == date.year)
    {
        if (month > date.month)
        {
            return true;
        }
        else if (month == date.month)
        {
            if (day >= date.day)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}
///

////Set and Get functions:
////
void Date::set_year(short year)
{
    this->year = year;
}

void Date::set_month(short month)
{
    this->month = month;
}

void Date::set_day(short day)
{
    this->day = day;
}

short Date::get_year() const
{
    return year;
}

short Date::get_month() const
{
    return month;
}

short Date::get_day() const
{
    return day;
}
////

/////Date functions:
/////
bool Date::isLeap()
{
    if (year % 4 != 0)
    {
        return false;
    }
    else if (year % 100 != 0)
    {
        return true;
    }
    else if (year % 400 != 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Date::isValid()
{
    if (year > 3000 || year < 1900)
    {
        return false;
    }
    if (month < 1 || month > 12)
    {
        return false;
    }
    if (day < 1 || day > 31)
    {
        return false;
    }
    if (month == 2)
    {
        if (isLeap())
        {
            return (day <= 29);
        }
        else
        {
            return (day <= 28);
        }
    }
    if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        return (day <= 30);
    }
    return true;
}
/////