#include<iostream>

void* operator new(size_t size){
    void* ptr = malloc(size);
    std::cout << "[new]: [" << size << " Bytes] allocated on heap at location:" << ptr << std::endl;
    return ptr;
}

void operator delete(void* ptr){
    free(ptr);
    std::cout << "[delete]: Memory freed from heap at location:" << ptr << std::endl;
}

int main(){
    int numbers_s[3];
    int* numbers_h = new int[30];
}