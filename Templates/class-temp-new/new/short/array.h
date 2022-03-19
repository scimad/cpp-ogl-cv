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
