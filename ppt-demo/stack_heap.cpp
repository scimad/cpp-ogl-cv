#include <iostream>

int main(){
    std::cout << "Hello World" << std::endl;
    int a = 20;
    {
        int a = 15;
        std::cout << "a = " << a;
    }

    std::cout << "a = " << a;

    int numbers[5] = {1, 2, 3, 4, 5};

    int* numbers_heap = new int[5];

}
