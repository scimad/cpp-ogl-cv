#ifndef __MY_STRING__
#define __MY_STRING__
#include <cstring>
#include "../custom-alloc/custom-alloc.hpp"

class myString{
    size_t len=0;
public:
    char* charBuf;// = new char[0];
    myString(){
        std::cout << "[myString]: Creating..." << std::endl;
        len = 0;
    }

    myString(const char* str):myString(){
        // delete[] charBuf;
        len = strlen(str);
        charBuf = new char[len+1];
        for (size_t i=0; i<len; i++){
            charBuf[i] = str[i];
        }
        charBuf[len] = '\0';
    }

    //create new charBuf while copying
    myString(const myString& my_str):myString(my_str.charBuf){
        std::cout << "[myString]: Copying..." << std::endl;
    }

    myString(const myString&& my_str):myString(my_str.charBuf){
        std::cout << "[myString]: Moving!!!" << std::endl;
    }

    ~myString(){
        std::cout << "[myString]: Deleting..." << std::endl;
        delete[] charBuf;
        len = 0;
    }

    friend std::ostream& operator<<(std::ostream& os, const myString& my_str){
        os << my_str.charBuf;
        return os;
    }
};
#endif

