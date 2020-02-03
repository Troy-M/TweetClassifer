#include <iostream> 
#include "training.h"
#include "DSString.h" 
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

using namespace std; 


int main(int argc, char** argv){
    if(argc == 1){
        return Catch::Session().run( argc, argv );
        //Testing template
    } else {
        //Command line format
        //<train data> <train target> <test data> <test target> <output>

        DSString train_data = argv[1];
        DSString train_target = argv[2];

        DSString test_data = argv[3];
        DSString test_target = argv[4];

        DSString output = argv[5];

        create_algo(train_data, train_target, test_data, test_target, output);
    }
}