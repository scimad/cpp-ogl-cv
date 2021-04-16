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
    this->_size = list->size() + 1;
    this->ptr = new t[this->_size];
    this->replaceFirst(element);

    for (int i=0; i<list->size(); i++){
        *(ptr+(1+i)) = * (list->ptr+i);
    }
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
        rest_list.ptr = new t[this->size()-1];
        rest_list._size = this->size()-1;
        for (int i=0; i<rest_list.size(); i++)
        {
           *(rest_list.ptr+i) = *(this->ptr+i+1);
        }
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
T ZList<T>::last(){
    std::cout << "So you need last element?" << std::endl;
    if (this->IsEmptyList()){
        std::cout << "I am an empty list" << std::endl;
        throw std::runtime_error("Error: List is empty.");
    }else {
        std::cout << "I am not an empty list" << std::endl;
        if (this->rest().IsEmptyList()){
            std::cout << "this->rest() is an empty list" <<std::endl;
            return this->first();
        }
        else{
            std::cout << "this->rest().last()"<<std::endl;
            return this->rest().last();
        }
    }
};

template <typename T>
void ZList<T>::replaceFirst(T newElement){
    if (this->IsEmptyList()){
        this->ptr = new T();
        this->_size+=1;
    }

    *this->ptr = newElement;
};
template class ZList<int>;
