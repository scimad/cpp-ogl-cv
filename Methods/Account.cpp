#include "Account.h"
Account::Account(){
}

Account::~Account(){
}

int& Account::salary(const int year, int& sal1, int& sal2){
    if (year > 50)
        return sal2;
    else
	return sal1;

}
