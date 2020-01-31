#include <iostream>
using namespace std;

void mystery2(int *m , int *n, int **o){
    int * temp = new int[3];
    temp[0] = temp[1] = temp[2] = 2;
    m = temp;
    *m = 4;
    n[1] = 6;
    n = temp;
    *o = temp;
    **o = 5;
}

int main(){
    int arr01[3] = {3,2,1};
    int arr02[4] = {5,2,4,3};
    
    int * d1 = arr01;
    int * d2 = arr02;
    int * d3;
    
    mystery2(d1,d2,&d3);

    cout << d1[0] << " " << d1[1] << endl;
    cout << d2[0] << " " << d2[1] << endl;
    cout << d3[0] << " " << d3[1] << endl;
    
}