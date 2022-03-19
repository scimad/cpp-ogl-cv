// compile script:
// To get array.o file --> g++ -c array.cpp 
// g++ -o main Array_t.cpp array.cpp
// to disable warning messages -w


#include "myarray.h"
#include <iostream>
using namespace std;
const int& max = 999;

typedef Array <int, 999> IntArr;

// typedef Array <double, 100> DoubleArr;

int main(){
	IntArr arr1;
    return 0;
}
