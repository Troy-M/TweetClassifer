#include "DSString.h"
#include <cstring>
#include <vector>
#include <iostream>
#include <cctype>

using namespace std;

//Helper function to allocate memory
void DSString::init(const char *input)
{
    //Add room for null termination
    size_t length = strlen(input) + 1;

    data = new char[length];
    memcpy(data, input, length);
}

DSString::DSString()
{
    data = nullptr;
}

DSString::~DSString()
{
    delete[] data;
}

DSString::DSString(char *input)
{
    init(input);
}

DSString::DSString(const char *input)
{
    init(input);
}

DSString::DSString(const DSString &copy)
{
    init(copy.data);
}

DSString &DSString::operator=(const DSString &other)
{
    if (this != &other)
    {
        delete[] data;
        init(other.data);
    }
    return *this;
}

DSString &DSString::operator=(const char *other)
{
    //If data is not the same pointer
    //Update pointer
    if (data != other)
    {
        delete[] data;
        init(other);
    }

    return *this;
}

DSString DSString::operator+(const DSString &other)
{
    //Allocate room for both plus null terminator
    char *tmp = new char[strlen(data) + strlen(other.data) + 1];

    strcpy(tmp, data);
    strcat(tmp, other.data);

    DSString output = tmp;

    //We're free to delete tmp
    delete[] tmp;

    return output;
}

bool DSString::operator==(const DSString &other) const
{
    return strcmp(data, other.data) == 0;
};

std::ostream &operator<<(std::ostream &out, const DSString &c)
{
    out << c.data;
    return out;
}

bool DSString::operator<(const DSString &other) const
{
    return strcmp(data, other.data) > 0;
};

int DSString::length() const
{
    return strlen(data);
}

std::vector<DSString *> DSString::split(char find) const
{
    std::vector<DSString *> output;

    int start = 0;
    char *occur = strchr(data, find);
    while (occur != nullptr)
    {
        DSString * sub = new DSString(substring(start, occur - data));
        output.push_back(sub);

        start = occur - data + 1;
        occur = strchr(occur + 1, find);
    }

    //Final substring
    DSString * sub = new DSString(substring(start, strlen(data)));
    output.push_back(sub);

    return output;
};

DSString DSString::substring(int start, int end) const
{
    //Technically the biggest the substring could be is the entire string
    char *tmp = new char[length()];

    //Bounds checking
    if(start > end){
        return "";
    }

    //Protect bounds
    end = min(end, length());

    for (int i = start; i < end; i++)
    {
        tmp[i - start] = data[i];
    };

    tmp[end - start] = '\0';

    DSString output = tmp;
    delete[] tmp;

    return output;
};

void DSString::toLower()
{
    for (int i = 0; i < length(); i++)
    {
        data[i] = tolower(data[i]);
    }
}

bool DSString::isASCII() const
{
    for (int i = 0; i < length() - 1; i++)
    {
        int check = static_cast<int>(data[i]);
        if (check > 127 || check < 0)
        {
            return false;
        }
    }
    return true;
}

void DSString::filter(DSString filter)
{
    DSString output = "";

    //This is the first occur
    char *occur = strstr(data, filter.data);

    if (occur == nullptr)
    {
        return;
    }

    int start = occur - data;
    int end = start + filter.length();

    output = substring(0, start) + substring(end, length());
    occur = strstr(output.data, filter.data);

    while (occur != nullptr)
    {
        int start = occur - output.data;
        int end = start + filter.length();

        output = output.substring(0, start) + substring(end, output.length());

        occur = strstr(output.data, filter.data);
    }

    delete[] data;
    init(output.data);
}

bool DSString::includes(const DSString &other) const
{
    char *output = strstr(data, other.data);

    return output != nullptr;
};

int DSString::atoi() const
{
    return std::atoi(data);
}

char *DSString::c_str() const
{
    return data;
}

