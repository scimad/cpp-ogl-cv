#include <zlist.hpp>

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

template class ZList<int>;
