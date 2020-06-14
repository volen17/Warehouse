#include "string.hpp"
#pragma once

class Location
{
public:
    Location();
    Location(String, String, short);
    Location(const Location &);
    Location &operator=(const Location &);

    void set_section(String);
    void set_shelf(String);
    void set_number(short);

    String get_section() const;
    String get_shelf() const;
    short get_number() const;

    friend std::ostream &operator<<(std::ostream &, const Location &);

private:
    String section;
    String shelf;
    short number;
};