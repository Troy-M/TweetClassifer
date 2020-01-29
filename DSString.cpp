#include "DSString.h"
#include <cstring>
#include <vector>
#include <iostream>
#include <cctype>

using namespace std;

//Helper function to allocate memory
void DSString::init(const char * input){
    //Add room for null termination
    size_t length = strlen(input) + 1;

    data = new char[length];
    memcpy(data, input, length);
}

DSString::DSString(){
    data = 0;
}

DSString::~DSString(){
    delete[] data;
}

DSString::DSString(char * input){
    init(input);
}

DSString::DSString(const char * input){
    init(input);
}

DSString::DSString(const DSString & copy){
    init(copy.data);
}

DSString & DSString::operator=(const DSString& other){
    if(this != &other){
        delete[] data;
        init(other.data);
    }
    return *this;
}

DSString & DSString::operator=(const char * other){
    //If data is not the same pointer
    //Update pointer
    if(data != other){
        delete []data;
        init(other);
    }

    return *this;
}

DSString DSString::operator+(const DSString & other){
    //Allocate room for both plus null terminator
    char * tmp = new char[strlen(data) + strlen(other.data) + 1];

    strcpy(tmp, data);
    strcat(tmp, other.data);

    DSString output = tmp;

    //We're free to delete tmp
    delete[] tmp;

    return output;
}

bool DSString::operator == (const DSString & other){
    return strcmp(data, other.data) == 0;
};

std::ostream & operator << (std::ostream &out, const DSString &c){
    out << c.data;
    return out;
} 

bool DSString::operator < (const DSString& other) const {
    return strcmp(data, other.data) < 0;
};

int DSString::length(){
    return strlen(data);
}

std::vector<DSString> DSString::split(char find){
    std::vector<DSString> output;

    int start = 0;
    char * occur = strchr(data, find);
    while(occur != NULL){
        DSString sub = substring(start, occur-data);
        output.push_back(sub);

        start = occur-data+1;
        occur = strchr(occur+1, find);
    }
    
    //Final substring
    DSString sub = substring(start, strlen(data));
    output.push_back(sub);

    return output;
};

DSString DSString::substring(int start, int end){
    //Technically the biggest the substring could be is the entire string
    char * tmp = new char[length()];

    for(int i = start; i < end; i++){
        tmp[i-start] = data[i];
    };

    tmp[end-start] = '\0';

    DSString output = tmp;
    delete [] tmp;

    return output;
};

DSString DSString::lower(){
    char * tmp = new char[length()];

    for(int i = 0; i < length(); i++){
        tmp[i] = tolower(data[i]);
    }

    tmp[length()] = '\0';

    DSString output = tmp;
    delete [] tmp;

    return output;
}

bool DSString::isASCII(){
    for(int i = 0; i < length()-1; i++){
        int check = static_cast<int>(data[i]); 
        if(check > 127 || check < 0){
            return false;
        } else {
            cout << data[i] << " " << check << endl;
        }
    }
    return true;
}

bool DSString::includes(const DSString & other){
    char * output = strstr(data, other.data);

    return output != nullptr;
};

int DSString::atoi(){
    return std::atoi(data);
}
