#include "tweet.h"
#include <iostream>
#include "DSString.h"

Tweet::Tweet(DSString * text, DSString * user, DSString * id)
{
    this->text = text;
    this->id = id;
    this->user = user;
}

Tweet::~Tweet()
{
    delete text;
    delete id;
    delete user;
}

Tweet::Tweet(const Tweet &copy)
{
    //This is safe sinec we know DSString does deep copy
    text = new DSString(*copy.text);
    id = new DSString(*copy.id);
    user = new DSString(*copy.user);
    classification = new int(*copy.classification);
}

Tweet &Tweet::operator=(const Tweet &other)
{
    if (this != &other)
    {
        delete this;

        text = new DSString(*other.text);
        id = new DSString(*other.id);
        user = new DSString(*other.user);
        classification = new int(*other.classification);
    }    
    return *this;
}



Tweet::Tweet(DSString * text, DSString * user, DSString * id, int * classification){
    
    this->text = text;
    this->id = id;
    this->user = user;
    this->classification = classification;
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

int * Tweet::GetClassification()
{
    return classification;
}

void Tweet::SetClassification(int classification)
{
    this->classification = new int(classification);
}