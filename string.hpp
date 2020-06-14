#include <fstream>
#pragma once

class String
{
public:
    String();
    String(const char *);
    String(const String &);
    String &operator=(const String &);
    String &operator=(const char *);
    ~String();

    friend std::istream &operator>>(std::istream &, String &);
    friend std::ostream &operator<<(std::ostream &, const String &);
    
    bool operator==(const char *) const;
    bool operator==(const String &) const;
    char &operator[](int pos);
    const char &operator[](int pos) const;
    String &operator=(char);
    String operator+(char);

    int length() const;
    int get_count() const;
    String get_word(int pos) const;
    String get_onWord(int pos) const;
    String get_fromWord(int pos) const;

    double get_double() const;
    int get_int() const;
    char *getRawString() const;
    bool isOnlyDateCharacters() const;
    bool isOnlyNumbers() const;

private:
    char *array;
};