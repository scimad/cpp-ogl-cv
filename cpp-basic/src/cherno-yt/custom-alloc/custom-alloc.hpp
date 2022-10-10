#ifndef __CUSTOM_ALLOC__
#define __CUSTOM_ALLOC__

#include <stddef.h>
#include <stdlib.h>
#include <iostream>

namespace zr
{
    bool custom_alloc_verbose = true;
} // namespace zr

void* operator new(size_t size){
    void* ptr = malloc(size);
    if (zr::custom_alloc_verbose == true)
        std::cout << "[new]: [" << size << " Bytes] allocated on heap at location:" << ptr << std::endl;
    return ptr;
}

void operator delete(void* ptr){
    free(ptr);
    if (zr::custom_alloc_verbose == true)
        std::cout << "[delete]: Memory freed from heap at location:" << ptr << std::endl;
}

void* operator new[](size_t size){
    void* ptr = malloc(size);
    if (zr::custom_alloc_verbose == true)
        std::cout << "[new[]]: [" << size << " Bytes] allocated on heap at location:" << ptr << std::endl;
    return ptr;
}

void operator delete[](void* ptr, size_t size){
    if (zr::custom_alloc_verbose == true)
        std::cout << "[delete[]]: Freeing up heap memory at location:" << ptr << std::endl;
    free(ptr);
}

#endif