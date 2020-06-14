#include "string.hpp"
#include <cstring>
#include <stdlib.h>
#include <iostream>

int String::length() const
{
    if (array != nullptr)
    {
        return strlen(array);
    }
    return 0;
}

String::String()
{
    array = nullptr;
}

char &String::operator[](int pos)
{
    return array[pos];
}

const char &String::operator[](int pos) const
{
    return array[pos];
}

String::String(const char *arg)
{
    array = new char[strlen(arg) + 2];
    strcpy(array, arg);
    array[length() + 1] = '\0';
}

String &String::operator=(const String &other)
{
    if (this != &other)
    {
        if (array != nullptr)
            delete[] array;
        array = new char[other.length() + 1];
        strcpy(array, other.array);
    }
    return *this;
}

String::~String()
{
    if (array != nullptr)
        delete[] array;
}

String &String::operator=(char c)
{
    if (array != nullptr)
        delete[] array;
    array = new char[2];
    array[0] = c;
    array[1] = '\0';
    return *this;
}

String String::operator+(char c)
{
    String result;
    result.array = new char[length() + 2];
    if (array != nullptr)
        strcpy(result.array, array);
    result.array[length()] = c;
    result.array[length() + 1] = '\0';
    return result;
}

bool String::operator==(const String &other) const
{
    return *this == other.array;
}

String::String(const String &other)
{
    array = new char[other.length() + 1];
    strcpy(array, other.array);
}

std::istream &operator>>(std::istream &in, String &string)
{

    char c{};
    if (string.length() == 0)
    {
        while (c != '\n')
        {
            c = in.get();
            if (c != '\n')
            {
                string = string + c;
            }
        }
    }
    else
    {
        string = "";
        while (c != '\n')
        {
            c = in.get();
            if (c != '\n')
            {
                string = string + c;
            }
        }
    }
    return in;
}

std::ostream &operator<<(std::ostream &out, const String &string)
{
    out << string.array;
    return out;
}

bool String::operator==(const char *arg) const
{
    if (length() != strlen(arg))
    {
        return false;
    }
    else
    {
        for (int i = 0; i < length(); i++)
        {
            if (array[i] != arg[i])
            {
                return false;
            }
        }
        return true;
    }
}

int String::get_count() const
{
    int word_count = 0;
    for (int i = 0; i < length(); i++)
    {
        if (array[i] == ' ')
        {
            word_count++;
        }
    }
    if (word_count != 0)
    {
        word_count++;
    }
    return word_count;
}

String &String::operator=(const char *str)
{
    delete[] array;
    array = new char[strlen(str) + 2];
    strcpy(array, str);
    array[length() + 1] = '\0';
    return *this;
}

String String::get_word(int pos) const
{
    String s;
    for (int i = pos; i < length(); i++)
    {
        if (array[i] == ' ' || array[i] == '\n')
        {
            break;
        }
        s = s + array[i];
    }
    return s;
}

String String::get_onWord(int pos) const
{
    String s;
    int cnt = 1;
    for (int i = 0; i < length(); i++)
    {
        if (cnt == pos)
        {
            return get_word(i);
        }
        if (array[i] == ' ')
        {
            cnt++;
        }
    }
    return "";
}

String String::get_fromWord(int pos) const
{
    String s;
    int cnt = 1;
    int i = 0;
    while (i < length())
    {
        if (cnt == pos)
        {
            break;
        }
        if (array[i] == ' ')
        {
            cnt++;
        }
        i++;
    }
    for (i; i < length(); i++)
    {
        s = s + array[i];
    }
    return s;
}

double String::get_double() const
{
    return atof(getRawString());
}

int String::get_int() const
{
    return atoi(getRawString());
}

char *String::getRawString() const
{
    return array;
}

bool String::isOnlyDateCharacters() const
{
    int cnt = 0;
    for (int i = 0; i < length(); i++)
    {
        if (cnt > 2)
        {
            return false;
        }
        if (array[i] == '-')
        {
            cnt++;
        }
        else if (!(array[i] >= 48 && array[i] <= 57))
        {
            return false;
        }
    }
    if (cnt < 2)
    {
        return false;
    }
    return true;
}

bool String::isOnlyNumbers() const
{
    int cnt = 0;
    for (int i = 0; i < length(); i++)
    {
        if (cnt > 1)
        {
            return false;
        }
        if (array[i] == '.')
        {
            cnt++;
        }
        else if (!(array[i] >= 48 && array[i] <= 57))
        {
            return false;
        }
    }
    return true;
}