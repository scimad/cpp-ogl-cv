// compile script:
// To get array.o file --> g++ -c array.cpp 
// g++ -o main Array_t.cpp array.cpp
// to disable warning messages -w

// main.cpp
#include "array.h"

#include <iostream>
using namespace std;
typedef Array <int, 999> IntArr;
int main(){
    IntArr arr1;
    return 0;
}