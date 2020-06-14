#include "product.hpp"
#include "string.hpp"
#include "date.hpp"
#include <iostream>

Product::Product()
{
    name = "Unknown";
    expiry_date = Date();
    arrival_date = Date();
    manufacturer_name = "Unknown";
    unit = "Unknown";
    quantity = 0.0;
    location = Location();
    comment = "";
    all_quantity = 0.0;
}

Product::Product(String name, Date expiry_date, Date arrival_date, String manufacturer_name, String unit, double quantity, String comment)
{
    this->name = name;
    this->expiry_date = expiry_date;
    this->arrival_date = arrival_date;
    this->manufacturer_name = manufacturer_name;
    this->unit = unit;
    this->quantity = quantity;
    this->location = location;
    this->comment = comment;
    this->all_quantity = 0.0;
}

Product::Product(const Product &other)
{
    name = other.name;
    expiry_date = other.expiry_date;
    arrival_date = other.arrival_date;
    manufacturer_name = other.manufacturer_name;
    unit = other.unit;
    quantity = other.quantity;
    location = other.location;
    comment = other.comment;
    all_quantity = other.all_quantity;
}

Product &Product::operator=(const Product &other)
{
    if (this != &other)
    {
        name = other.name;
        expiry_date = other.expiry_date;
        arrival_date = other.arrival_date;
        manufacturer_name = other.manufacturer_name;
        unit = other.unit;
        quantity = other.quantity;
        location = other.location;
        comment = other.comment;
        all_quantity = other.all_quantity;
    }
    return *this;
}

std::ostream &operator<<(std::ostream &out, const Product &product)
{
    out << "Name: " << product.name << std::endl
        << "Expiry date: " << product.expiry_date << std::endl
        << "Arrival date: " << product.arrival_date << std::endl
        << "Manufacturer name: " << product.manufacturer_name << std::endl
        << "Quantity: " << product.quantity << " " << product.unit << std::endl
        << "All quantity of this type of product: " << product.all_quantity << " " << product.unit << std::endl
        << "Location: " << std::endl
        << product.location
        << "Comment: " << product.comment << std::endl;
    return out;
}

void Product::set_name(String name)
{
    this->name = name;
}

void Product::set_expiry_date(Date expiry_date)
{
    this->expiry_date = expiry_date;
}

void Product::set_arrival_date(Date arrival_date)
{
    this->arrival_date = arrival_date;
}

void Product::set_manufacturer_name(String manufacturer_name)
{
    this->manufacturer_name = manufacturer_name;
}

void Product::set_unit(String unit)
{
    this->unit = unit;
}

void Product::set_quantity(double quantity)
{
    this->quantity = quantity;
}

void Product::set_location(Location location)
{
    this->location = location;
}

void Product::set_comment(String comment)
{
    this->comment = comment;
}

void Product::set_all_quantity(double all_quantity)
{
    this->all_quantity = all_quantity;
}

String Product::get_name() const
{
    return name;
}

Date Product::get_expiry_date() const
{
    return expiry_date;
}

Date Product::get_arrival_date() const
{
    return arrival_date;
}

String Product::get_manufacturer_name() const
{
    return manufacturer_name;
}

String Product::get_unit() const
{
    return unit;
}

double Product::get_quantity() const
{
    return quantity;
}

Location Product::get_location() const
{
    return location;
}

String Product::get_comment() const
{
    return comment;
}

double Product::get_all_quantity() const
{
    return all_quantity;
}