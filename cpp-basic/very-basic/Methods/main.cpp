#include "Account.h"
#include <iostream>
using namespace std;
int main(){
    int a = 25;
    Account ac;
    //cout << "The salary is about " << ac.salary(a) << endl;
    int m = 25000;
    int n = 50000;
    const int& s1 = 25555;
    const int& s2 = 50555;
    const int& k = ac.salary(55, s1, s2);
    const int* p = &k;
    cout << "The address of s1 is " << &s1 << endl;
    cout << "The address of s2 is " << &s2 << endl;
    cout << "The address of return is " << p << endl;
    // k = 99999;
    cout << "The new value of s2 is " << s2 << endl;

    cout << "The address held by const int* p is " << p << endl;

    char str[] = "Nepal is heading to a mysterious direction";
    cout << str << endl;
    cout << (void *) str << endl;

}
