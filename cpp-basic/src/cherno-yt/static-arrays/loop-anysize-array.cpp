#include <array>
#include <iostream>

template<std::size_t SIZE>
void printArray(std::array<int, SIZE>& arr, const int times) {
    for (int i=0; i<times; i++){
        for(auto& e : arr) {
            std::cout << e << " ";
        }
        std::cout << std::endl;
    }
}

int main()
{
    std::array<int, 1> arr1 = {1};
    std::array<int, 2> arr2 = {1, 2};
    std::array<int, 3> arr3 = {1, 2, 3};
    printArray(arr1, 3);
    printArray(arr2, 5);
    printArray(arr3, 2);
}
