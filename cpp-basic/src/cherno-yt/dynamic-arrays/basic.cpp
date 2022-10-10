#include <iostream>

#include "../custom-strings/mystring.hpp"
#include "./dynaimc-array.hpp"

class vec3{
    float x, y, z;
};

int main(){
    typedef vec3 T1;
    DynamicArray<T1> d1_arr(3);
    d1_arr.push_back(T1());
    d1_arr.push_back(T1());
    d1_arr.push_back(T1());
    d1_arr.push_back(T1());
    d1_arr.push_back(T1());

    typedef std::string T2;
    DynamicArray<T2> d2_arr(5);
    d2_arr.push_back(T2("Test"));
    d2_arr.push_back(T2("Test"));
    d2_arr.push_back(T2("Test"));
    d2_arr.push_back(T2("Test"));
    d2_arr.push_back(T2("Test"));
    d2_arr.push_back(T2("Test"));
    d2_arr.push_back(T2("Test"));

    typedef myString T3;
    DynamicArray<T3> d3_arr(5);
    d3_arr.push_back(T3("Custom"));
    d3_arr.push_back(T3("Custom"));
    d3_arr.push_back(T3("Custom"));
    d3_arr.push_back(T3("Custom"));
    d3_arr.push_back(T3("Custom"));
    d3_arr.push_back(T3("Custom"));
    d3_arr.push_back(T3("Custom"));

return 0;
}
