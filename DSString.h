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


        bool operator == (const DSString &);
        friend std::ostream & operator << (std::ostream &out, const DSString &c); 
        int length();

        bool isASCII();

        //Get int representation
        int atoi();

        bool includes(const DSString &);

        std::vector<DSString> split(char);
        DSString substring(int, int);

        DSString lower();

    private:
        void init(const char *);

        char * data;
};

#endif