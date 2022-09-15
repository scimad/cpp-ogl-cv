#include <iostream>

class Vec2f
{
private:
    float x,y;
public:
    Vec2f(float x, float y):x(x),y(y){};
    ~Vec2f(){};
    float getX(){
        return x;
    };
    float getY(){
        return y;
    };

    void setX(float x){
        (*this).x = x;
    };
    void setY(float y){
        (*this).y = y;
    };

    Vec2f operator+(Vec2f v){
        return Vec2f(x+v.x, y+v.y);
    };

    Vec2f& operator<<(float k){
        setX(getX()*k);
        setY(getY()*k);
        return *this;
    };

    Vec2f operator>>(float k){
        setX(getX()*k);
        setY(getY()*k);
        return *this;
    };
};


std::ostream& operator<<(std::ostream& stream, Vec2f v){
    stream << "(" << v.getX() << ", " << v.getY() << ")";
    return stream;
}


// The following is same (?) as defining Vec2f& Vec2f::operator<<(). i.e. inside Vec2f class
// Vec2f& operator<<(Vec2f& v, float k){
//     v.setX(v.getX()*k);
//     v.setY(v.getY()*k);
//     return v;
// }


int main(int argc, char const *argv[])
{
    auto v1 = Vec2f(1, 1);
    auto v2 = Vec2f(4, 5);
    std::cout << v1 << std::endl;
    std::cout << v2 << std::endl;

    std::cout << v1 << std::endl;
    std::cout << v2 << std::endl;

    std::cout << v1 + v2 << std::endl;

    v1 << 100;
    std::cout << v1 << std::endl;
}
