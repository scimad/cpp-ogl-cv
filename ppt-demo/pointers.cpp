#include <iostream>

int main(){
    int a = 10;
    int* p;
    std::cout << "Address stored in p is " << p << std::endl;
    //std::cout << "The value stored in that address is " << *p << std::endl;


    p = nullptr;
    std::cout << "Address stored in p is " << p << std::endl;
    //std::cout << "The value stored in that address is " << *p << std::endl;

    (p)++;

    std::cout << "Address stored in p is " << p << std::endl;
    std::cout << "The value stored in that address is " << *p << std::endl;


    p = &a;
    std::cout << "Address stored in p is " << p << std::endl;
    std::cout << "The value stored in that address is " << *p << std::endl;

    (*p)++;

    std::cout << "Address stored in p is " << p << std::endl;
    std::cout << "The value stored in that address is " << *p << std::endl;

}