// C++ program to illustrate the concept of dynamic binding
#include <iostream>
using namespace std;
 
class B
{
    public:
 
    // Virtual function
    virtual void f() {
        cout << "The base class function is called.\n";
    }
};
 
class D: public B
{
    public:
    void f() {
        cout << "The derived class function is called.\n";
    }
};
 
int main()
{
    B base;
    D derived;
 
    B *basePtr = &base;
    basePtr->f();
 
    basePtr = &derived;
    basePtr->f();
 
    return 0;
}




//Credit: https://www.techiedelight.com/difference-between-static-dynamic-binding-cpp/