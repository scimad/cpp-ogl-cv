#include <array>
#include <iostream>

class A{
public:
    std::string name;
    A(std::string n){
        name = n;
    };
    virtual void test(){
        std::cout << "Running test for A" << std::endl;
        std::cout << "Name: " << name << std::endl;
    };

};

class B : public A{
public:
    std::string surname;
    B(std::string n, std::string s):A(n){
        surname = s;
    };
    void test(){
        std::cout << "Running test for B" << std::endl;
        std::cout << "Surname: " << surname << std::endl;
        A::test();
    };

};

class C : public A{

};

int main()
{

    A* a = new B("Madhav", "Humagain");
    a->test();

    std::cout << "Downcasting example." << std::endl;
    B* b = dynamic_cast<B*>(a);
    b->surname = "Sharma";

    if (b){
        std::cout << "Casting was successful." << std::endl;
        b->test();
    }else{
        std::cout << "Casting was not successful." << std::endl;
    }
    std::cout << "Upcasting example." << std::endl;
    A* a2 = b;
    a2->test();

}
