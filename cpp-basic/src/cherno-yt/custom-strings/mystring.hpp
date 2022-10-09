#ifndef __MY_STRING__
#define __MY_STRING__
#include <cstring>
#include "../custom-alloc/custom-alloc.hpp"

class myString{
    size_t len=0;
public:
    char* charBuf;// = new char[0];
    myString(){
        std::cout << "[myString]: Calling default constructor for mystring." << std::endl;
        len = 0;
        // delete[] charBuf;
        // charBuf = new char[1];
        // charBuf[0] = '\0';
    }

    myString(const char* str){
        // delete[] charBuf;
        len = strlen(str);
        charBuf = new char[len+1];
        std::cout << "[myString]: Creating a new mystring from const char* of length " << len << std::endl;
        for (size_t i=0; i<len; i++){
            charBuf[i] = str[i];
        }
        charBuf[len] = '\0';
    }

    //create new charBuf while copying
    myString(const myString& my_str):myString(my_str.charBuf){
        std::cout << "[myString]: Copy constructor invoked." << std::endl;
    }

    ~myString(){
        delete[] charBuf;
        len = 0;
    }

    friend std::ostream& operator<<(std::ostream& os, const myString& my_str){
        os << my_str.charBuf;
        return os;
    }
};
#endif

