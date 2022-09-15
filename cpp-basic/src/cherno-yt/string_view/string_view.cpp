#include <string>
#include <string_view>
#include <iostream>
int main(){
    std::string name = "Madhav Humagain";
    std::string test = name.c_str();
    name = "Apple Ball";
    std::string_view v_test(name.c_str() + 3 , 5);
    std::cout << v_test << std::endl;

    char c_string[] = "Hi, this is Madhav";
    std::cout << "c_string = " << c_string << std::endl;
    std::string_view v2_test(c_string + 12, 6);

    *(c_string + 12) = 'm';
    std::cout << v2_test << std::endl;
}
