#include "WordCounts.h"
#include "DSString.h"
#include<vector>
using namespace std;

WordCounts::WordCounts(){
    pos = vector<int>();
    neg = vector<int>();
    words = vector<DSString*>();
}

void WordCounts::AddWord(DSString * word, bool positive){
    bool found = false;
    for(int i = 0; i < words.size() && !found; i++){
        if(*words[i] == *word){
            pos[i] += positive;
            neg[i] += !positive;
            found = true;
        }
    }

    if(!found){
        words.push_back(word);
        pos.push_back(positive);
        neg.push_back(!positive);
    }
}

void WordCounts::Print(){
    for(int i = 0; i < words.size(); i++){
        cout << *words[i] << " " << pos[i] << " " << neg[i] << endl;
    }
}