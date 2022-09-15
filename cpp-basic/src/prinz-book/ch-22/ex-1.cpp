#include<iostream>

class FloatArr
{
private:
    float* arrPtr;
    int max;
    int cnt;
public:
    FloatArr(int n=256);
    FloatArr(int n, float val);
    FloatArr(const FloatArr& src);
    ~FloatArr();
    int length() const {return cnt;}
    float& operator[] (int i);
    float operator[] (int i) const;
    FloatArr& operator=( const FloatArr&);
    bool append(float val);
    bool remove(int pos);
};

FloatArr::FloatArr(int n)
{
    max = n;
    cnt = 0;
    arrPtr = new float[max];
}

FloatArr::FloatArr(int n, float val)
{
    max = cnt = n;
    arrPtr = new float[max];
    for (int i=0; i<cnt; i++)
        arrPtr[i] = val;
}

FloatArr::FloatArr(const FloatArr& src)
{
    max = src.max;
    cnt = src.cnt;
    arrPtr = new float[max];
    for (int i=0; i<cnt; i++)
        arrPtr[i] = src.arrPtr[i];
}

//Overloading the assignment
/*
- release the memory referenced by the dynamic members
- allocate sufficient memory and copy the source object’s data to that memory.

This is required because the default assignment
and the standard copy constructor isn't suitable
for classes with dynamic members as the default
assignment and the copy constructor would only
copy the pointers and not a separate copy of the
values.
*/
FloatArr& FloatArr::operator= (const FloatArr& src)
{
    if (this != &src)
    {
        max = src.max;
        cnt = src.cnt;
        delete[] arrPtr;
        arrPtr = new float[max];
        for (int i=0; i<cnt; i++)
            arrPtr[i] = src.arrPtr[i];
    }
    return *this;
}



FloatArr::~FloatArr()
{
    delete[] arrPtr;
}


int main(int argc, char const *argv[])
{
    FloatArr v(10);
    FloatArr w(20, 1.0F);
    std::cout<<sizeof(FloatArr)<<std::endl;
    
    return 0;
}

