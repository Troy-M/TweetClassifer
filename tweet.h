#ifndef TWEET_H
#define TWEET_H

#include "DSString.h"

class Tweet {
    public:
        //No reason we would want to change these later
        //Or why we dont know them at creation
        Tweet(DSString text, DSString user, DSString id);
        Tweet(DSString text, DSString user, DSString id, int classification);

        DSString GetText();
        DSString GetID();
        DSString GetUser();
        
        int GetClassification();

        //This could be set after loading
        //ie running through model    
        void SetClassification(int);

    private:
        DSString text;
        DSString id;
        DSString user;
        int classification;
};

#endif