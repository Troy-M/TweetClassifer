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

        //Creation operators
        DSString & operator = (const DSString&);
        DSString & operator = (const char *);
        DSString   operator + (const DSString &);
        
        //Comparison operators
        //Used for std::map
        bool operator< (const DSString&) const; 
        bool operator == (const DSString &) const;

        //std::cout overload
        friend std::ostream & operator << (std::ostream &out, const DSString &c);

        //Remove a given phrase in string
        void filter(const DSString& filter);

        //Change string to lower case
        void toLower();

        std::vector<DSString*> split(char) const;
        DSString substring(int, int) const;

        bool isASCII() const;
        bool includes(const DSString &) const;
        
        int atoi() const; //Get int representation
        int length() const;

        char * c_str() const;

    private:
        void init(const char *);
        char * data;
        int size;
};

#endif