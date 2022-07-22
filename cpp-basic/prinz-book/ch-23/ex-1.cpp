//Inheritance
/*
Author        : scimad2.71@gmail.com
Written       : 10th May, 2020
Last Modified : 10th May, 2020 
*/
#include <iostream>
#include <string>
using namespace std;
class Base
{
protected:
    string s;
    int id;
public:
    Base(int a, const string& n){s = n; id = a;}
    ~Base();
};

Base::~Base()
{
}

class Derived : public Base
{
private:
    string extra;
public:
    Derived(const string& desc, const string& n, int a):Base(a, n), extra(desc){}
    ~Derived();
    void display()
    {
        cout<<s<<"  "<<id<<"  "<<extra<<endl;
    }
};

Derived::~Derived()
{
}



int main(int argc, char const *argv[])
{
    Derived d("I am the description", "madhav", 27);
    d.display();
    return 0;
}
