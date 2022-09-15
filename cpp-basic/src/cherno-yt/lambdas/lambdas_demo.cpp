#include <iostream>
int main(int argc, char const *argv[])
{
    int a = 10;
    int b = 20;

    auto lambda_func = [&a, b](){
        a = a * 10;
        return (a + b)/2;
    };

    std::cout << lambda_func()<< std::endl;

    a+=100;
    b+=200;
    std::cout << lambda_func()<< std::endl;

    std::cout << "a = " << a << " and b = " << b << std::endl;

    auto lambda_div_func = [a, b] (int divisor){
        return (a + b ) / divisor;
    };

    std::cout << "A + B divided by 5 is " << lambda_div_func(5) << std::endl;

}
