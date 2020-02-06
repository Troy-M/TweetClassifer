#ifndef TRAINING_H
#define TRAINING_H

#include "DSString.h" 
#include "Tweet.h"
#include "WordCounts.h"
#include <vector>
using namespace std;

void create_algo(const DSString&, const DSString&, const DSString&, const DSString&, const DSString&);
bool filter_tweet(DSString * word);
void check_biagram(DSString *, DSString *);
WordCounts gen_dict(vector<Tweet>);
WordCounts run_training(vector<Tweet>);
void write_errors(vector<Tweet>, float, const DSString&);
void run_inference(WordCounts, vector<Tweet>, const DSString&);
vector<Tweet> load_pairs(const DSString&, const DSString&);

#endif
