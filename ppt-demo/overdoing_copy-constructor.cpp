#include<iostream>
#include<cstring>

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

    String(const String& other){
        //C++'s default constructor does this: memcpy(this, &other, sizeof(String))
        //which is equivalent to mBuffer = other.mBuffer; m_Size = other.mSize();


        //Following code does deep copying!
        std::cout << "Copy constructor invoked" << std::endl;
        m_Size = other.m_Size;
        m_Buffer = new char[m_Size + 1];
        memcpy(m_Buffer, other.m_Buffer, m_Size + 1);
    }
};

int main(){
    
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