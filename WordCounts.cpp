#include "WordCounts.h"
#include "DSString.h"
#include<vector>
using namespace std;

WordCounts::WordCounts(){
    pos = vector<int>();
    neg = vector<int>();
    words = vector<DSString*>();
    indices = std::map<DSString, int>();

}

void WordCounts::AddWord(DSString * word, bool positive){
    try {
        int index = indices.at(*word);
        pos[index] += positive;
        neg[index] += !positive;

    } catch(std::out_of_range){
        
        words.push_back(word);
        pos.push_back(positive);
        neg.push_back(!positive);

        pair<DSString, int> cache(*word, words.size()-1);
        indices.insert(cache);
    }
}

void WordCounts::Print(){
    for(int i = 0; i < words.size(); i++){
        cout << *words[i] << " " << pos[i] << " " << neg[i] << endl;
    }
}