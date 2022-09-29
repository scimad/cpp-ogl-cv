#include <iostream>
#include <array>
#include <string>
#include <stdexcept>
#include <cstring>

void* operator new(size_t size){
    void* ptr = malloc(size);
    std::cout << "[" << size << " Bytes] allocated on heap at location:" << ptr << std::endl;
    return ptr;
}

void operator delete(void* ptr){
    free(ptr);
    std::cout << "delete: Memory freed from heap at location:" << ptr << std::endl;
}

void* operator new[](size_t size){
    void* ptr = malloc(size);
    std::cout << "operator new[]: [" << size << " Bytes] allocated on heap at location:" << ptr << std::endl;
    return ptr;
}

void operator delete[](void* ptr, size_t size){
    std::cout << "operator delete[]: Freeing up heap memory at location:" << ptr << std::endl;
    free(ptr);
}

typedef std::string T;
class DynamicArray{
private:
    size_t n;
    size_t capacity;
    T* resize();
    void push_back();
    T at(size_t index);
    T* Tbuffer = nullptr;

public:
    DynamicArray(size_t size = 10){
        std::cout << "DynamicArray: Creating DA of size " << size << "."<< std::endl;
        this->capacity = size;
        this->n = size;
        // Heap Allocation
        Tbuffer = new T[capacity];
    }

    DynamicArray(size_t size, T _default):DynamicArray(size){
        std::cout<< "DynamicArray: Initialized array with value: " << _default << std::endl;
        for (size_t i = 0; i < size; i++){
            Tbuffer[i] = _default;
        }
    }

    ~DynamicArray(){
        std::cout<< "~DynamicArray: Calling destructor." << std::endl;
        delete[] Tbuffer;//, capacity;
    };

    //For assignment and access
    T& operator[](size_t index){
        std::cout << " Implementation 1" << std::endl;
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
        std::cout << "resize: Resizing from " << capacity << " to " << new_capacity << "." << std::endl;

        T* newBuffer = new T[new_capacity];
        for (size_t i=0; i<(new_capacity?new_capacity<capacity:capacity); ++i){
            newBuffer[i] = Tbuffer[i];
        }
        capacity = new_capacity;
        delete[] Tbuffer;
        Tbuffer = newBuffer;
        std::cout << "resize: Resized." << std::endl;
        return Tbuffer;
    }
};

int main()
{
    DynamicArray arr(10, "Madhav");
    // arr[3] = "Humagain";
    // std::cout << "arr[3] = " << arr[3] << std::endl;
    arr.resize(15);
}
