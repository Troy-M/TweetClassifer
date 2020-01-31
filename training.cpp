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
        while (getline(raw_tweets, line) && i < 5000000){
            DSString str = line.c_str(); 
            vector<DSString*> parts = str.split(',');

            //Some tweets contain commas
            //This would be parts[4],parts[5] etc
            //We can loop over these and join them back
            DSString * text = parts[3];
            for(int i = 4; i < parts.size(); i++){
                *text = *text + *parts[i];
            }

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
        while (getline(raw_target, line) && index < 5000000){
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

bool filter_tweet(DSString * word){
    word->toLower();

    //Check for empty words
    if(*word == ""){
        return false;
    }

    //Links
    if(word->includes("http://")){
        return false;
    }

    //These may be at the end of the word and we want seperated from the word
    //They must be checked here because they arent alphabetical
    //This is a while becuase of .... or ???
    while(word->includes("?") || word->includes(".") || word->includes("!")){
        *word = word->substring(0, word->length()-1);                
    }

    //There is a chance our word only was endings
    if(*word == ""){
        return false;
    }

    //Check if its an emoji
    if(!word->isASCII()){
        return false;
    }

    //Filter out letters we dont care about
    word->filter("\"");
    word->filter("&quot;");
    word->filter("&lt;");
    word->filter("&amp");
    word->filter(")");
    word->filter("("); 
    word->filter("'");
    word->filter("=");


    //Words that are common
    word->filter("a");
    word->filter("an");
    word->filter("the");
    word->filter("to");
    word->filter("you");
    word->filter("i");
    word->filter("then");
    word->filter("is");
    word->filter("are");



    //Filter out one letter words
    //These are largely numbers
    if(word->length() < 2){
        return false;
    }

    return true;
}

WordCounts * gen_dict(vector<Tweet*> * data){
    //word -> (positive count, negative count)
    auto * word_counts = new WordCounts();

    //Loop through every tweet, split it into words
    //Update word count
    for(int i = 0; i < data->size(); i++){
        Tweet * tweet = data->at(i);
        vector<DSString*> parts = tweet->GetText()->split(' ');

        for(int j = 0; j < parts.size(); j++){
            DSString * word = parts[j];

            if(!filter_tweet(word)){
                continue;
            };

            word_counts->AddWord(word, tweet->GetClassification());
        }

        if(i % 30000 == 0){ 
            float percent_done = (float)i / data->size() * 100;
            cout << "Trained on " << i << " tweets. Progress: " << int(percent_done) << "%" << endl;
        }
    }

    return word_counts;
}

WordCounts * run_training(vector<Tweet*> * data){
    WordCounts * words = gen_dict(data);
    words->GenScores();

    cout << "Ran training on " << words->Size() << " words" << endl;

    return words;
}

void run_inference(WordCounts * weights, vector<Tweet*> * data){
    int right = 0;
    int wrong = 0;
    for(int i = 0; i < data->size(); i++){
        Tweet * tweet = data->at(i);

        float score = 0;

        auto scores = vector<float>();

        vector<DSString*> parts = tweet->GetText()->split(' ');

        for(int j = 0; j < parts.size(); j++){
            DSString * word = parts[j];

            if(!filter_tweet(word)){
                continue;
            };

            score += weights->GetScore(word);

            scores.push_back(score);
        }

        int prediction = (score / parts.size()) > 0;
        prediction *= 4;

        if(tweet->GetClassification() != prediction){
            //cout << "Wrong predicition, correct score: " << tweet->GetClassification() << " score: " << score << " Tweet: " << *tweet->GetText() <<  endl << " \t\t Breakdown: [";

            for(int i = 0; i < scores.size(); i++){
                cout << scores[i] << ',';
            }

            cout << ']' << endl;

            wrong++;
        } else {
            right++;            
        }
    }
    
    cout << "Correct: " << right << endl;
    cout << "Incorrect: " << wrong << endl;
    cout << "Total: " << right + wrong << endl;
    cout << "Accuracy: " << (float)right / (right+wrong) << endl;
}

//Main entry loop from main
//Load data, train algo, test algo, write output
void create_algo(string train_data, string train_target, string test_data, string test_target, string output)
{
    vector<Tweet*> * training = load_pairs(train_data, train_target);

    cout << "Done loading training data. " << training->size() << " loaded" << endl;
    
    vector<Tweet*> * testing = load_pairs(test_data, test_target);

    cout << "Done loading testing data. " << testing->size() << " loaded" << endl;

    WordCounts * weights = run_training(training);

    //cout << "Test against training data" << endl;
    //run_inference(weights, training);

    cout << "Test against testing data" << endl;
    run_inference(weights, testing);
}