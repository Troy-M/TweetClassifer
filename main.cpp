#include <iostream> 
#include "training.h"
using namespace std; 


int main(int argc, char** argv){
    if(argc == 1){
        //Testing template
    } else {
        //Command line format
        //<train data> <train target> <test data> <test target> <output>

        string train_data = argv[1];
        string train_target = argv[2];

        string test_data = argv[3];
        string test_target = argv[4];

        string output = argv[5];

        create_algo(train_data, train_target, test_data, test_target, output);
    }
}