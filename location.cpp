#include "location.hpp"
#include "string.hpp"
#include <fstream>
#include <iostream>

///Constructors / operator= / operator<< :
///
Location::Location()
{
    section = "Unknown";
    shelf = "Unknown";
    number = 0;
}

Location::Location(String section, String shelf, short number)
{
    this->section = section;
    this->shelf = shelf;
    this->number = number;
}

Location::Location(const Location &other)
{
    section = other.section;
    shelf = other.shelf;
    number = other.number;
}

Location &Location::operator=(const Location &other)
{
    if (this != &other)
    {
        section = other.section;
        shelf = other.shelf;
        number = other.number;
    }
       return *this;
}

std::ostream &operator<<(std::ostream &out, const Location &location)
{
    out << " > section: " << location.section << std::endl
        << " > shelf: " << location.shelf << std::endl
        << " > number: " << location.number << std::endl;
	return out;
}
///

////Set and Get functions:
////
void Location::set_section(String section)
{
    this->section = section;
}

void Location::set_shelf(String shelf)
{
    this->shelf = shelf;
}

void Location::set_number(short number)
{
    this->number = number;
}

String Location::get_section() const
{
    return section;
}

String Location::get_shelf() const
{
    return shelf;
}

short Location::get_number() const
{
    return number;
}
////

/////Location functions:
/////

/////