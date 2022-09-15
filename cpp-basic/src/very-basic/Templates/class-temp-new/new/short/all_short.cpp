// array.h
#ifndef _ARRAY_H_
#define _ARRAY_H_
#include <iostream>
using namespace std;
template <class T, int n=256>
class Array{
    private:
    T arr[n]; // The array
    int cnt; // Current number of elements
        public:
    Array();
    Array(int m, const T& val );
};
#endif

// array.cpp
//#include <array.h>

template <class T, int n>
Array<T, n>::Array(){
    cnt = 0;
    cout << "An array was created" << endl;
} 

template <class T, int n >
Array<T, n>::Array(int m, const T& val ){
    cnt = m;
    for(int i=0; i < cnt; i++ )
        arr[i] = val;
}

// main.cpp
// #include <array.h>

#include <iostream>
using namespace std;
typedef Array <int, 999> IntArr;
int main(){
    IntArr arr1;
    return 0;
}