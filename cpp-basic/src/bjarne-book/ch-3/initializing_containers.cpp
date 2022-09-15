#include <iostream>
#include <fstream>

class Vector
    {
    private:
        double* elem;
        int sz;
    public:
        // Vector (){ Vector(0); } //This gives seg. fault but the following doesn't
        Vector ():elem{new double[0]},sz{0}{} //This works fine but above doesn't


        Vector (int s):elem{new double[s]},sz{s}
        {
            for (int i=0; i!=s; ++i)
            { 
                elem[i] = 0;
            }
        }
        Vector(std::initializer_list<double> l):Vector(0)
        {
            for (auto a:l){
                this->push_back(a);
            }
        };
        ~Vector(){delete[] elem;};
        double& operator[](int i);
        int size() const;
        void push_back(double d)
        {   elem[sz++] = d;

        };

        void show()
        {
            for (int i=0; i!=sz; i++){
                std::cout<<elem[i]<<std::endl;
            }
            if (sz == 0)
                std::cout<<"Nothing to show"<<std::endl;
        
        };
    };

int main(int argc, char const *argv[])
{
    Vector v1 = {1, 11, 111};
    v1.show();

    Vector v2;
    v2.show();

}
