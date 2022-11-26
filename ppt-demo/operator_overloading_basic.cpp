#include <iostream>

class Complex
{
public:
    float x, y;
    Complex(float a, float b):x(a), y(b){};
    ~Complex(){};

    Complex operator+(const Complex z){
        return Complex(this->x+z.x, this->y+z.y);
    }

    Complex operator*(const Complex z){
        float a, b, c, d;
        a = this->x;
        b = this->y;
        c = z.x;
        d = z.y;
        return Complex(a*c-b*d, a*d+b*c);
    }

    std::string val(){
        return std::to_string(x) + " + " + std::to_string(y) + "i";
    }
};

int main(){
    Complex z1 = Complex(1,2);
    Complex z2 = Complex(3,4);
    Complex z = z1 * z2;
    std::cout <<z.val()<< std::endl;
}