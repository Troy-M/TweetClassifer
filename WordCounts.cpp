#include "WordCounts.h"
#include "DSString.h"
#include<vector>
#include <numeric>
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

void WordCounts::Sort() {

    //Generate a new vector the same size as words
    //Fill it with the numbers between 0 and words.size()
    //Sort these indices based on pos + neg 
    std::vector<int> y(words.size());
    std::iota(y.begin(), y.end(), 0);

    auto comparator = [&](int a, int b){ return pos[a]+neg[a] > pos[b]+neg[b]; };
    std::sort(y.begin(), y.end(), comparator);

    int i = 0;
    for(auto v : y){
        cout << *words[v] << " " << pos[v] << " " << neg[v] << endl;
        i++;

        if(i > 50){
            return;
        }
    }
}
