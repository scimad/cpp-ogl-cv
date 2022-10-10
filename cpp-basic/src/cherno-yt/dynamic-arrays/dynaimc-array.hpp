#include <iostream>
#include <stdexcept>

#include "../custom-alloc/custom-alloc.hpp"
#include "../custom-strings/mystring.hpp"

template<typename T>
class DynamicArrayIterator{
    T** m_Ptr;
public:
    DynamicArrayIterator(T** ptr):m_Ptr(ptr){};

    DynamicArrayIterator<T>& operator++(){
        m_Ptr++;
        return *this;
    };

    // Not being able to write the following override version
    // DynamicArrayIterator<T> operator++(){
    //     DynamicArrayIterator<T> it = *this;
    //     ++(*this);
    //     return it;
    // };

    DynamicArrayIterator<T>& operator--(){
        m_Ptr--;
        return *this;
    };

    // Not being able to write the following override version
    // DynamicArrayIterator<T> operator--(){
    //     DynamicArrayIterator<T> it = *this;
    //     --(*this);
    //     return it;
    // };

    T& operator[](size_t index){
        return **(m_Ptr+index);
    };

    T* operator->(){
        return *m_Ptr;
    };

    T& operator*(){ //to ensure assignments
        return **m_Ptr;
    };

    bool operator == (const DynamicArrayIterator& other) const{
        return m_Ptr == other.m_Ptr;
    };

    bool operator != (const DynamicArrayIterator& other) const{
        return !(m_Ptr == other.m_Ptr);
    };
};

template <typename T>
class DynamicArray{
private:
    size_t n;
    size_t capacity;
    T** resize();
    T at(size_t index);
    T** T_ptr = new T*[0];

    // returns new location if succesful and nullptr if allocation wasn't succesful
    T** resize(size_t new_capacity){
        std::cout << "[resize]: Resizing from " << capacity << " to " << new_capacity << "." << std::endl;
        T** newT_ptr = new T*[new_capacity];
        for (size_t i=0; i<(new_capacity<capacity?new_capacity:capacity); ++i){
            //need to copy pointers of objects
            newT_ptr[i] = T_ptr[i];
        }
        capacity = new_capacity;
        delete[] T_ptr;
        T_ptr = newT_ptr;
        std::cout << "[resize]: Resized." << std::endl;
        return T_ptr;
    }

public:
    DynamicArray(size_t size = 10){
        std::cout << "[DynamicArray]: Creating..."<< std::endl;
        this->capacity = size;
        this->n = 0;
        // Heap Allocation
        delete[] T_ptr;
        T_ptr = new T*[capacity];
    }

    DynamicArray(size_t size, T _default):DynamicArray(size){
        if (zr::custom_alloc_verbose == true)
            std::cout<< "[DynamicArray]: Initialized array with value: " << _default << std::endl;
        for (size_t i = 0; i < size; i++){
            this->push_back(_default);
        }
    }

    ~DynamicArray(){
        std::cout<< "[~DynamicArray]: Calling destructor." << std::endl;

        //while deleting Dynamic Array, free up memory reserved by its objects
        for (size_t i=0; i<n;i++){
            (*T_ptr[i]).~T();
        }
        delete[] T_ptr;
    };

    DynamicArrayIterator<T> begin(){
        return DynamicArrayIterator<T>(T_ptr);
    };

    DynamicArrayIterator<T> end(){
        return DynamicArrayIterator<T>(T_ptr + n); //pointer arithmetic
    };

    //To access the data
    const T& operator[](size_t index) const{
        if (index<n)
            return *(T_ptr[index]);
        else
            throw std::invalid_argument("Invalid index size");
    }

    //To modify data
    T& operator[](size_t index){
        if (index<n)
            return *(T_ptr[index]);
        else
            throw std::invalid_argument("Invalid index size");
    }

    // void push_back(const T& value){
    //     if (n == capacity){
    //         // resize the array and copy to new place
    //         this->resize((this->capacity+1)*3/2);
    //     }
    //     if (zr::custom_alloc_verbose == true)
    //         std::cout << "[push_back]:Pushing back (at index " << n << ")." << std::endl;
    //     //invoke move semantics
    //     this->T_ptr[n] = new T(std::move(value)); //new T(value);
    //     n++;
    // }

    void push_back(const T&& value){
        if (n == capacity){
            // resize the array and copy to new place
            this->resize((this->capacity+1)*3/2);
        }
        if (zr::custom_alloc_verbose == true)
            std::cout << "[push_back]:Pushing back (at index " << n << ")." << std::endl;
        //invoke move semantics
        this->T_ptr[n] = new T(std::move(value)); //new T(value);
        n++;
    }

    void pop_back(){//T&& pop_back(){
        if (n>0){
            n--;
            // return std::move(*T_ptr[n]);
            (*T_ptr[n]).~T();
        }else{
            throw std::invalid_argument("Invalid index size");
        }
    }

    size_t size() const {return n;}

    void print_all(){
        for (size_t i=0; i<this->size(); i++){
            std::cout << (*this)[i] << std::endl;
        }
    }
};
