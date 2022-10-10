#include <iostream>

#include "../custom-strings/mystring.hpp"
#include "./dynaimc-array.hpp"
#include "../custom-alloc/custom-alloc.hpp"

extern bool zr::custom_alloc_verbose;
class Vec3{
    float x, y, z;
public:
    ~Vec3(){
        std::cout << "[Vec3]: Destroying..." << std::endl;
    }
    Vec3():Vec3(0,0,0){
        std::cout << "[Vec3]: Creating..." << std::endl;
    }
    Vec3(float x, float y, float z): x(x), y(y), z(z){
        std::cout << "[Vec3]: Creating..." << std::endl;
    }
    Vec3(const Vec3& v):Vec3(v.x, v.y, v.z){
        std::cout << "[Vec3]: Copying..." << std::endl;
    }
    Vec3(const Vec3&& v):x(v.x), y(v.y), z(v.z){
        std::cout << "[Vec3]: Moving!!!" << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vec3& v){
        os <<  "(" << v.x << ", " << v.y << ", " << v.z << ")";
        return os;
    }
};

int main(){
    typedef Vec3 T1;
    DynamicArray<T1> d1_arr(3);
    zr::custom_alloc_verbose = true;
    d1_arr.push_back(T1(1,2,3));
    d1_arr.push_back(T1());
    d1_arr.push_back(T1());
    d1_arr.push_back(T1());
    d1_arr.push_back(T1());

    d1_arr.print_all();

    d1_arr.pop_back();
    // d1_arr.pop_back();


    // typedef std::string T2;
    // DynamicArray<T2> d2_arr(5);
    // zr::custom_alloc_verbose = true;
    // d2_arr.push_back(T2("Test"));
    // d2_arr.push_back(T2("Test"));
    // d2_arr.push_back(T2("Test"));
    // d2_arr.push_back(T2("Test"));
    // d2_arr.push_back(T2("Test"));
    // d2_arr.push_back(T2("Test"));
    // d2_arr.push_back(T2("Test"));
    // d2_arr.print_all();


    // typedef myString T3;
    // DynamicArray<T3> d3_arr(5);
    // zr::custom_alloc_verbose = true;
    // d3_arr.push_back("Custom");
    // d3_arr.push_back(T3("Custom 1"));
    // d3_arr.push_back(T3("Custom 2"));
    // d3_arr.push_back(T3("Custom 3"));
    // d3_arr.push_back(T3("Custom 4"));
    // d3_arr.push_back(T3("Custom String"));
    // d3_arr.print_all();

    // d3_arr.pop_back();
    // d3_arr.pop_back();

return 0;
}
