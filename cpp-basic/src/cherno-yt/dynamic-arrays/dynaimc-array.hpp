#include <iostream>
#include <stdexcept>

#include "../custom-alloc/custom-alloc.hpp"
#include "../custom-strings/mystring.hpp"


typedef myString T;
// typedef std::string T;
class DynamicArray{
private:
    size_t n;
    size_t capacity;
    T* resize();
    void push_back();
    T at(size_t index);
    T* T_objects = nullptr;

    // returns new location if succesful and nullptr if allocation wasn't succesful
    T* resize(size_t new_capacity){
        std::cout << "resize: Resizing from " << capacity << " to " << new_capacity << "." << std::endl;

        T* newBuffer = new T[new_capacity];
        for (size_t i=0; i<(new_capacity?new_capacity<capacity:capacity); ++i){
            //need to invoke copy constructor
            newBuffer[i] = std::move(T_objects[i]);
        }
        capacity = new_capacity;
        delete[] T_objects;
        T_objects = newBuffer;
        std::cout << "resize: Resized." << std::endl;
        return T_objects;
    }

public:
    DynamicArray(size_t size = 10){
        std::cout << "DynamicArray: Creating DA of size " << size << "."<< std::endl;
        this->capacity = size;
        this->n = 0;
        // Heap Allocation
        T_objects = new T[capacity];
    }

    DynamicArray(size_t size, T _default):DynamicArray(size){
        std::cout<< "DynamicArray: Initialized array with value: " << _default << std::endl;
        for (size_t i = 0; i < size; i++){
            // T_objects[i] = _default;
            this->push_back(_default);
        }
    }

    ~DynamicArray(){
        std::cout<< "~DynamicArray: Calling destructor." << std::endl;
        delete[] T_objects;//, capacity;
    };

    //To access the data
    const T& operator[](size_t index) const{
        if (index<n)
            return T_objects[index];
        else
            throw std::invalid_argument("Invalid index size");
    }

    //To modify data
    T& operator[](size_t index){
        if (index<n)
            return T_objects[index];
        else
            throw std::invalid_argument("Invalid index size");
    }

    void push_back(const T& value){
        if (n == capacity){
            // resize the array and copy to new place
            this->resize((this->capacity+1)*3/2);
        }
        this->T_objects[n] = value;
        n++;
    }

    size_t size() const {return n;}

    void print_all(){
        for (size_t i=0; i<this->size(); i++){
            std::cout << (*this)[i] << std::endl;
        }
    }
};
