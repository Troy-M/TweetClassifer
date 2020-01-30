#include <iostream>
#include <fstream>
#include "DSString.h"
#include "tweet.h"
#include <vector>
#include <map>
#include "WordCounts.h"

using namespace std;

vector<Tweet*> * load_pairs(string data, string target){
    //Step one load the training data
    vector<Tweet*> * output = new vector<Tweet*>;

    string line;
    ifstream raw_tweets(data);
    if (raw_tweets.is_open()){
        //CSV header, ignore        
        getline(raw_tweets, line);

        //TODO: Remove to train against entire dataset
        int i = 0;
        while (getline(raw_tweets, line) && i < 50000){
            DSString str = line.c_str(); 
            vector<DSString*> parts = str.split(',');

            Tweet * tweet = new Tweet(parts[3], parts[2], parts[1]->atoi());

            output->push_back(tweet);

            i++;
        }
        raw_tweets.close();
    }

    ifstream raw_target(target);
    if (raw_target.is_open()){
        //CSV header, ignore        
        getline(raw_target, line);

        int index = 0;

        //We assume that data and target files include the same tweets
        while (getline(raw_target, line) && index < 50000){
            DSString str = line.c_str(); 
            vector<DSString*> parts = str.split(',');

            int classification = parts[1]->atoi();
            output->at(index)->SetClassification(classification);
            index += 1;
        }

        raw_target.close();
    }

    return output;
}

void gen_dict(vector<Tweet*> * data){
    //word -> (positive count, negative count)
    auto * word_counts = new WordCounts();

    //Loop through every tweet, split it into words
    //Update map based on classification
    for(int i = 0; i < 5000; i++){
        Tweet * tweet = data->at(i);
        vector<DSString*> parts = tweet->GetText()->split(' ');

        for(int j = 0; j < parts.size(); j++){
            DSString * word = parts[j];

            word->toLower();

            //Check for empty words
            if(*word == ""){
                continue;
            }

            //Links
            if(word->includes("http://")){
                continue;
            }

            //These may be at the end of the word and we want seperated from the word
            //They must be checked here because they arent alphabetical
            //This is a while becuase of .... or ???
            while(word->includes("?") || word->includes(".") || word->includes("!")){
                *word = word->substring(0, word->length()-1);                
            }

            //There is a chance our word only was endings
            if(*word == ""){
                continue;
            }

            //Check if its an emoji
            if(!word->isASCII()){
                continue;
            }

            //Filter out letters we dont care about
            word->filter("\"");
            word->filter("&quot;");
            word->filter("&lt;");
            word->filter(")");
            word->filter("("); 
            word->filter("'");


            //Filter out one letter words
            //These are largely numbers
            if(word->length() == 1){
                continue;
            }

            int result = tweet->GetClassification();
            word_counts->AddWord(word, result);
        }
    }

    word_counts->Print();

    //return word_counts;
}

void run_training(vector<Tweet*> * data){
    gen_dict(data);
}

//Main entry loop from main
//Load data, train algo, test algo, write output
void create_algo(string train_data, string train_target, string test_data, string test_target, string output)
{
    vector<Tweet*> * training = load_pairs(train_data, train_target);
    
    cout << "Done loading training data. " << training->size() << " loaded" << endl;
    
    vector<Tweet*> * testing = load_pairs(test_data, test_target);

    cout << "Done loading testing data. " << testing->size() << " loaded" << endl;

    run_training(training);
}