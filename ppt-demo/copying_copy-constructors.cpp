#include<iostream>
#include<cstring>

class Vec3
{
public:
    float x,y,z;
    Vec3(float x, float y, float z):x(x), y(y), z(z){};
    ~Vec3(){};
    
    std::string val(){
        return std::to_string(x) + "i + " + std::to_string(y)  + "j + " + std::to_string(z)  + "k";
    }
};


class String{
    public:
        char* m_Buffer;
        unsigned int m_Size;
    
    String(const char* string){
        m_Size = strlen(string);
        m_Buffer = new char[m_Size+1];
        memcpy(m_Buffer, string, m_Size);
        m_Buffer[m_Size] = '\0';
    }
    
    friend std::ostream& operator<<(std::ostream& stream, const String& string){
        stream << string.m_Buffer;
        return stream;
    }

    ~String(){
        delete[] m_Buffer;
    }

    // String(const String& other){
    //     //C++'s default constructor does this: memcpy(this, &other, sizeof(String))
    //     //which is equivalent to mBuffer = other.mBuffer; m_Size = other.mSize();


    //     //Following code does deep copying!
    //     std::cout << "Copy constructor invoked" << std::endl;
    //     m_Size = other.m_Size;
    //     m_Buffer = new char[m_Size + 1];
    //     memcpy(m_Buffer, other.m_Buffer, m_Size + 1);
    // }
};

int main(){
    
    // Copying primitive datatype
    int a = 2;
    int b = a;

    // Modifying a copy doesn't affect the original object
    b = 3;

    // Copying a complex datatype works the same way

    // auto v1 = Vec3(1, 0, 0);
    Vec3 v1 = {1, 0, 0};
    std::cout << v1.val() << std::endl;

    Vec3 v2 = Vec3(v1);

    //Heap Allocation of Vec3 Object
    //This doesn't make a copy of actual object
    Vec3* v3 = new Vec3(0,1,0);
    Vec3* v4 = v3;
    // The following modifies v3 as well.
    v4->x = 3;



    //Coyping example with string
    String str1 = "Ekbana";
    std::cout << str1 << std::endl;

    // Following line tries to copy!
    String str2 = str1;                 
    std::cout << str2 << std::endl;


    str2.m_Buffer[2] = 'm';
    std::cout << "Just tried to modify second string.." << std::endl;
    std::cout << str1 << std::endl;
    std::cout << str2 << std::endl;

    // Something goes wrong at the end of this program!!
    // It is because the C++'s default way of copying is by copying all the data members
    // which means copying the pointer as well. [i.e. shallow copy!]
    // which means the at the end of this scope, when the str1 and str2 are deleted,
    // same buffer is deleted twice!

    // Modifying the mBuffer of one string would alter the content of another string.

    // HENCE WE NEED A WELL WRITTEN COPY CONSTRUCTOR!!!!
}