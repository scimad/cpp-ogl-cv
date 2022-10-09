#ifndef __CUSTOM_ALLOC__
# define __CUSTOM_ALLOC__

#include <stddef.h>
#include <stdlib.h>
#include <iostream>

void* operator new(size_t size){
    void* ptr = malloc(size);
    std::cout << "[new]: [" << size << " Bytes] allocated on heap at location:" << ptr << std::endl;
    return ptr;
}

void operator delete(void* ptr){
    free(ptr);
    std::cout << "[delete]: Memory freed from heap at location:" << ptr << std::endl;
}

void* operator new[](size_t size){
    void* ptr = malloc(size);
    std::cout << "[new[]]: [" << size << " Bytes] allocated on heap at location:" << ptr << std::endl;
    return ptr;
}

void operator delete[](void* ptr, size_t size){
    std::cout << "[delete[]]: Freeing up heap memory at location:" << ptr << std::endl;
    free(ptr);
}

#endif