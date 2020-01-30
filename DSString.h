#ifndef DSSTRING_H
#define DSSTRING_H

#include <vector>
#include <iostream>

class DSString {

    public:
        DSString();
        DSString(char *);
        DSString(const char *);
        DSString(const DSString &);
        ~DSString();

        DSString & operator = (const DSString&);
        DSString & operator = (const char *);
        DSString   operator + (const DSString &);

        bool operator< (const DSString&) const;

        void filter(DSString filter);

        bool operator == (const DSString &);
        friend std::ostream & operator << (std::ostream &out, const DSString &c); 
        
        int length();
        bool isASCII();
        int atoi(); //Get int representation

        bool includes(const DSString &);

        void toLower();

        std::vector<DSString*> split(char);
        DSString substring(int, int);


    private:
        void init(const char *);

        char * data;
};

#endif