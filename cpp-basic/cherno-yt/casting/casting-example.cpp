#include <array>
#include <iostream>

class Base
{
public:
    Base(/* args */){};
    ~Base(){};
};

class Derived:public Base
{
public:
    Derived(/* args */){};
    ~Derived(){};
};

class AnotherDerived:public Base
{
public:
    AnotherDerived(/* args */){};
    ~AnotherDerived(){};
};

int main()
{
    float f = 3.5;
    int a = f;                          // C-style cast
    int b = static_cast<int>(f);         // C++ style cast
    Derived* derived = new Derived();   // create an instance of derived class
    Base* base = derived;               // store the derived pointer using base pointer
    AnotherDerived* ac = static_cast<AnotherDerived*>(base);    //

}
