#include <iostream>
#include <fstream>
#include "DSString.h"
#include "tweet.h"
#include <vector>
#include <map>

using namespace std;

vector<Tweet> load_pairs(string data, string target){
    //Step one load the training data
    vector<Tweet> output;

    string line;
    ifstream raw_tweets(data);
    if (raw_tweets.is_open()){
        //CSV header, ignore        
        getline(raw_tweets, line);

        while (getline(raw_tweets, line)){
            DSString str = line.c_str(); 
            vector<DSString> parts = str.split(',');

            Tweet tweet = Tweet(parts[3], parts[2], parts[1].atoi());

            output.push_back(tweet);
        }
        raw_tweets.close();
    }

    ifstream raw_target(target);
    if (raw_target.is_open()){
        //CSV header, ignore        
        getline(raw_target, line);

        int index = 0;

        //We assume that data and target files include the same tweets
        while (getline(raw_target, line)){
            DSString str = line.c_str(); 
            vector<DSString> parts = str.split(',');

            int classification = parts[1].atoi();
            output[index].SetClassification(classification);
            index += 1;
        }

        raw_target.close();
    }

    return output;
}

void run_training(vector<Tweet> data){
    //word -> (positive count, negative count)
    map<DSString,pair<int,int> > word_counts;

    //Loop through every tweet, split it into words
    //Update map based on classification
    for(int i = 0; i < 100; i++){
        Tweet tweet = data[i];
        vector<DSString> parts = tweet.GetText().split(' ');

        for(int j = 0; j < parts.size(); j++){
            DSString word = parts[j].lower();

            if(word == ""){
                continue;
            }

            if(word.includes("http://")){
                continue;
            }

            //These may be at the end of the word and we want seperated from the word
            //They must be checked here because they arent alphabetical
            //This is a while becuase of .... or ???
            while(word.includes("?") || word.includes(".") || word.includes("!")){
                word = word.substring(0, word.length()-1);                
            }

            if(word == ""){
                continue;
            }

            if(!word.isASCII()){
                continue;
            }

            int result = tweet.GetClassification();

            if(word_counts.find(word) == word_counts.end()){
                pair<int,int> placeholder(result != 0, result == 0); 
                pair<DSString, pair<int,int> > value(word, placeholder);

                word_counts.insert(value);
            } else {
                pair<int,int> value = word_counts.at(word);

                value.first += result != 0;
                value.second += result == 0;

                word_counts.at(word) = value;
            };
        }
    }

    for (auto const& x : word_counts){
        std::cout << '"' << x.first << '"' << ':' << x.second.first << ':' << x.second.second << std::endl;
    }
}

//Main entry loop from main
//Load data, train algo, test algo, write output
void create_algo(string train_data, string train_target, string test_data, string test_target, string output)
{
    vector<Tweet> training = load_pairs(train_data, train_target);
    
    cout << "Done loading training data. " << training.size() << " loaded" << endl;
    
    vector<Tweet> testing = load_pairs(test_data, test_target);

    cout << "Done loading testing data. " << testing.size() << " loaded" << endl;

    run_training(training);
}