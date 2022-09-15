#include<iostream>
#include <string>
template<class T>
void exchange (T& x, T& y){
    T help = x;
    x = y;
    y = help;
};

int main(int argc, char const *argv[])
{
    std::string a = "madhav", b = "universe";
    std::cout<<"before exchange:"<<std::endl;
    std::cout<<"a="<<a<<" and b="<<b<<std::endl;
    exchange (a, b);
    std::cout<<"After exchange:"<<std::endl;
    std::cout<<"a="<<a<<" and b="<<b<<std::endl;

    int x = 321, y = 222;
    std::cout<<"\n\nbefore exchange:"<<std::endl;
    std::cout<<"x="<<x<<" and y="<<y<<std::endl;
    exchange (x, y);
    std::cout<<"After exchange:"<<std::endl;
    std::cout<<"x="<<x<<" and y="<<y<<std::endl;

    return 0;
}