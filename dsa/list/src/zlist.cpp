#include <zlist.hpp>
#include <iostream>
#include <stdexcept>

template <typename t>
ZList<t>::ZList(){
    this->_size = 0;
    this->ptr = nullptr;
    // this->_max_size = 10;
    // this->ptr = new t[_max_size];
};

template <typename t>
ZList<t>::ZList(t element, ZList<t>* list){

};

template <typename t>
ZList<t>::~ZList(){
    delete [] this->ptr;
};

template <typename t>
t ZList<t>::first(){
    if (size()>0)
        return ptr[0];
    else 
        throw std::runtime_error("Error: List is empty.");

};

template <typename t>
ZList<t> ZList<t>::rest(){
    ZList<t> rest_list;
    if (!this->IsEmptyList())
    {
        rest_list.ptr = this->ptr+1;
        rest_list._size = this->size()-1;
    }
    return rest_list;
};

template <typename t>
bool ZList<t>::IsEmptyList(){
    if (size()==0)
        return true;
    else 
        return false;
};

template <typename T>
void ZList<T>::replaceFirst(T newElement){
    if (this->IsEmptyList()){
        this->ptr = new T();
        *this->ptr = newElement;
        this->_size+=1;
    }

    std::cout << "Successfully added " << newElement << " into list" << std::endl;
};
template class ZList<int>;
