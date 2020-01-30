#ifndef WORD_COUNTS_H
#define WORD_COUNTS_H

#include "DSString.h"
#include<vector>
#include<map>

class WordCounts {

    public:
        WordCounts();

        void AddWord(DSString *, bool positive);

        void Print();


    private:
        std::map<DSString, int> indices;
        std::vector<DSString*> words;
        std::vector<int> pos;
        std::vector<int> neg;

};

#endif