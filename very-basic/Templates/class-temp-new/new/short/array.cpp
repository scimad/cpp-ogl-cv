// array.cpp
#include "array.h"

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
