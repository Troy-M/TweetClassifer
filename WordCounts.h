#ifndef WORD_COUNTS_H
#define WORD_COUNTS_H

#include "DSString.h"
#include<vector>

class WordCounts {

    public:
        WordCounts();

        void AddWord(DSString *, bool positive);

        void Print();


    private:
        std::vector<DSString*> words;
        std::vector<int> pos;
        std::vector<int> neg;

};

#endif