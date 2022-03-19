#include "Account.h"
Account::Account(){
}

Account::~Account(){
}

const int& Account::salary(const int& year, const int& sal1, const int& sal2){
    if (year > 50)
        return sal2;
    else
        return sal1;

}
