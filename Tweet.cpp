#include "Tweet.h"
#include <iostream>
#include "DSString.h"

Tweet::Tweet(DSString * text, DSString * user, DSString * id)
{
    this->text = new DSString(*text);
    this->id = new DSString(*id);
    this->user = new DSString(*user);
    this->classification = 0;
}

Tweet::~Tweet()
{
    delete text;
    delete id;
    delete user;
}

Tweet::Tweet(const Tweet &copy)
{
    //This is safe since we know DSString does deep copy
    text = new DSString(*copy.text);
    id = new DSString(*copy.id);
    user = new DSString(*copy.user);
    classification = copy.classification;
}

Tweet &Tweet::operator=(const Tweet &other)
{
    if (this != &other){
        delete text;
        delete id;
        delete user;

        text = new DSString(*other.text);
        id = new DSString(*other.id);
        user = new DSString(*other.user);
        classification = other.classification;
    }    
    return *this;
}

DSString * Tweet::GetText()
{
    return text;
}

DSString * Tweet::GetID()
{
    return id;
}

DSString * Tweet::GetUser()
{
    return user;
}

int Tweet::GetClassification()
{
    return classification;
}

void Tweet::SetClassification(int c)
{
    this->classification = c;
}