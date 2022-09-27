#include <iostream>
#include <array>
#include <string>
#include <stdexcept>
#include <cstring>

// void* operator new(size_t size){
//     void* ptr = malloc(size);
//     std::cout << "[" << size << " Bytes] allocated on heap at location:" << ptr << std::endl;
//     return ptr;
// }

// void operator delete(void* ptr){
//     free(ptr);
//     std::cout << "Memory freed from heap at location:" << ptr << std::endl;
// }

void* operator new[](size_t size){
    void* ptr = malloc(size);
    std::cout << "[" << size << " Bytes] allocated on heap at location:" << ptr << std::endl;
    return ptr;
}

void operator delete[](void* ptr){
    free(ptr);
    std::cout << "Memory freed from heap at location:" << ptr << std::endl;
}

typedef std::string T;
class DynamicArray{
private:
    size_t n;
    size_t capacity;
    T* resize();
    void push_back();
    T at(size_t index);
    T *Tbuffer;

public:
    DynamicArray(size_t size = 10)
    {
        std::cout << "Creating DA of size " << size << "."<< std::endl;
        this->capacity = size;
        this->n = size;
        // Heap Allocation
        Tbuffer = new T[capacity];
    }

    DynamicArray(size_t size, T _default):DynamicArray(size){
        std::cout<< "Initialized array with value: " << _default << std::endl;
        for (size_t i = 0; i < size; i++){
            Tbuffer[i] = _default;
        }
    }

    ~DynamicArray(){
        delete[] Tbuffer;
    };

    //For assignment and access
    T& operator[](size_t index){
        if (index<n)
            return Tbuffer[index];
        else
            throw std::invalid_argument("Invalid index size");
    }

    void push_back(T&& value){
        n++;
        if (n == capacity){
            // resize the array and copy to new place
        }
    }

    // returns new location if succesful and nullptr if allocation wasn't succesful
    T* resize(size_t new_capacity){
        T* old_Buffer = Tbuffer;
        T* Tbuffer = new T[new_capacity];
        for (size_t i=0; i<capacity; ++i){
            Tbuffer[i] = old_Buffer[i];
        }
        delete[] old_Buffer;
        return Tbuffer;
    }
};

int main()
{
    // DynamicArray arr(10);
    DynamicArray arr(10, "Madhav");
    arr[3] = "Humagain";
    std::cout << "arr[3] = " << arr[3] << std::endl;
    arr.resize(15);
}
