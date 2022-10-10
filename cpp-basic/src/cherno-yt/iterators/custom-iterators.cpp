#include <iostream>
#include <vector>

#include "../custom-strings/mystring.hpp"
#include "../dynamic-arrays/dynaimc-array.hpp"

int main(){
    zr::custom_alloc_verbose = false;

    // typedef std::string T;
    typedef myString T;

    DynamicArray<T> dyn_arr;

    dyn_arr.push_back("Madhav");
    dyn_arr.push_back("Humagain");
    dyn_arr.push_back("Nepal");
    dyn_arr.push_back("Lalitpur");

    for (auto it = dyn_arr.begin(); it!= dyn_arr.end(); ++it){
        std::cout << *it << std::endl;
    }

    std::cout << "----------" << std::endl;
    auto it = dyn_arr.begin();
    std::cout << it[0] << std::endl;
    ++it;
    std::cout << it[0] << std::endl;
    --it;
    std::cout << it[0] << std::endl;

    std::cout << "----------" << std::endl;


    it = dyn_arr.begin();
    *it = T("Test User");
    for (auto it = dyn_arr.begin(); it!= dyn_arr.end(); ++it){
        std::cout << *it << std::endl;
    }
    std::cout << "----------" << std::endl;
    return 0;
}
