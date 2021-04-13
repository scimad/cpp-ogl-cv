#include <zlist.hpp>
#include <iostream>
#include <stdexcept>

template <typename t>
ZList<t>::ZList(){
    this->_size = 0;
    this->_max_size = 10;
    this->ptr = new t[_max_size];
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

template class ZList<int>;
