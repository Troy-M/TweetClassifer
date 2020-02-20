#ifndef WORD_COUNTS_H
#define WORD_COUNTS_H

#include "DSString.h"
#include <vector>
#include <map>
#include <utility>

class WordCounts {

    public:
        WordCounts();

        void AddWord(DSString, bool);

        float GetScore(DSString);
        void GenScores();

        int Size() const;

    private:
        std::map<DSString, int> indices;
        std::vector<DSString> words;
        std::vector<int> pos;
        std::vector<int> neg;
        std::vector<float> scores;

        float GenScore(int);

};

#endif