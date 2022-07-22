//Type Conversion in Class Hierarchies
/*
Author        : scimad2.71@gmail.com
Written       : 9th May, 2020
Last Modified : 9th May, 2020 
*/
#include <iostream>
#include <string>
using namespace std;

class Car
{
private:
    long nr;
    string producer;
public:
    Car(long n=0L, const string& prod="");
    long getNr(void) const {return nr;}
    void setNr(long n) {nr = n;}
    const string& getProd() const {return producer;}
    void setProd(const string& p) {producer = p;}
    void display(void) const;
    ~Car();
};
Car::Car(long n, const string& prod)
{
    nr = n;
    producer = prod; 
}
void Car::display() const
{
    std::cout<<"For this car, nr = "<<nr<<" & producer = "<<producer<<std::endl;
};
Car::~Car()
{
};

class PassCar : public Car
{
    private:
        string passCarType;
        bool sunRoof;
    public:
        PassCar (const string& tp, bool sd,
                 int n=0, const string& h ="");
        PassCar(Car& c);
        const string& getType() const { return passCarType;}
        void setType (const string s) {passCarType = s;}
        bool getSunRoof() const {return sunRoof;}
        void setSunRoof(bool b) {sunRoof = b;}
        void display() const;
};

PassCar::PassCar (const string& tp, bool sd,
                 int n, const string& h)
{
    passCarType = tp;
    sunRoof = sd;
    Car::setNr(n);
    Car::setProd(h);
}

PassCar::PassCar(Car& c)
{
    PassCar("default", 1,c.getNr(), c.getProd());
}

int main(int argc, char const *argv[])
{
    Car aut;
    PassCar bmw("520i", true, 4325, "Bayerische Motorenwerke");
    aut = bmw;
    aut.display();

    std::cout<<bmw.getSunRoof()<<std::endl;
    //The following line doesn't return error
    //only because we have defined PassCar(Car& c);
    std::cout<<(static_cast<PassCar>(aut)).getSunRoof()<<std::endl;
    
    return 0;
}
