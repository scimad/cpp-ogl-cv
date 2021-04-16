#include <zlist.hpp>
#include <iostream>
#include <stdexcept>

template <typename t>
ZList<t>::ZList(){
    this->_size = 0;
    this->ptr = nullptr;
};

template <typename t>
ZList<t>::ZList(const ZList<t>& list):ZList(){
    // copy constructor
    this->_size = list.size();
    this->ptr = new t[this->_size];

    for (int i=0; i<this->_size; i++){
        *(this->ptr+i) = *(list.ptr+i);
    }
};

template <typename t>
ZList<t>::ZList(t element, ZList<t>* list):ZList(){
    this->_size = list->size() + 1;
    this->ptr = new t[this->size()];
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
t ZList<t>::first() const{
    if (size()>0)
        return ptr[0];
    else 
        throw std::runtime_error("Error: List is empty.");

};

template <typename t>
ZList<t> ZList<t>::rest() const{
    ZList<t> rest_list;
    if (!this->IsEmptyList())
    {
        rest_list._size = this->size()-1;
        rest_list.ptr = new t[this->size()-1];
        for (int i=0; i<rest_list.size(); i++)
        {
           *(rest_list.ptr+i) = *(this->ptr+i+1);
        }
    }
    return rest_list;
};

template <typename t>
bool ZList<t>::IsEmptyList() const{
    if (size()==0)
        return true;
    else 
        return false;
};

template <typename T>
T ZList<T>::last() const{
    if (this->IsEmptyList()){
        throw std::runtime_error("Error: List is empty.");
    }else {
        if (this->rest().IsEmptyList()){
            return this->first();
        }
        else{
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

template <typename T>
void ZList<T>::append(T element){
    ZList<T> new_list = *this;
    this->_size = this->size()+ 1;
    delete []this->ptr;
    this->ptr = new T[this->size()];
    for (int i=0; i<this->size()-1; i++){
        *(this->ptr+i) = *(new_list.ptr+i);
    }
    *(this->ptr+(this->size()-1)) = element;
};

template <typename T>
void ZList<T>::append(ZList<T> list){
    for (int i=0; i<list.size(); i++){
        this->append(*(list.ptr+i));
    }
};

template class ZList<int>;
