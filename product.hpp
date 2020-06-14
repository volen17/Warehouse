#include "string.hpp"
#include "date.hpp"
#include "location.hpp"
#pragma once

class Product
{
public:
    Product();
    Product(String, Date, Date, String, String, double, String);
    Product(const Product &);
    Product &operator=(const Product &);

    void set_name(String);
    void set_expiry_date(Date);
    void set_arrival_date(Date);
    void set_manufacturer_name(String);
    void set_unit(String);
    void set_quantity(double);
    void set_location(Location);
    void set_comment(String);
    void set_all_quantity(double);

    String get_name() const;
    Date get_expiry_date() const;
    Date get_arrival_date() const;
    String get_manufacturer_name() const;
    String get_unit() const;
    double get_quantity() const;
    Location get_location() const;
    String get_comment() const;
    double get_all_quantity() const;

    friend std::ostream &operator<<(std::ostream &, const Product &);

private:
    String name;
    Date expiry_date;
    Date arrival_date;
    String manufacturer_name;
    String unit;
    double quantity;
    Location location;
    String comment;
    double all_quantity;
    };