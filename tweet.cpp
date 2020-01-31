#include "tweet.h"

Tweet::Tweet(DSString * text, DSString * user, DSString * id){
    this->text = text;
    this->id = id;
    this->user = user;
}

Tweet::Tweet(DSString * text, DSString * user, DSString * id, int classification){
    this->text = text;
    this->id = id;
    this->user = user;
    this->classification = classification;
}

DSString * Tweet::GetText(){
    return text;
}

DSString * Tweet::GetID(){
    return id;
}

DSString * Tweet::GetUser(){
    return user;
}

int Tweet::GetClassification(){
    return classification;
}

void Tweet::SetClassification(int classification){
    this->classification = classification;
}