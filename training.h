#ifndef TRAINING_H
#define TRAINING_H

#include "DSString.h" 

void create_algo(DSString train_data, DSString train_target, DSString test_data, DSString test_target, DSString output);
bool filter_tweet(DSString * word);

#endif
