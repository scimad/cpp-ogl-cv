#include<iostream>
#include<cstring>

static int copy_count = 0;

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
        std::cout << "Copy constructor of String class invoked." << std::endl;
        m_Size = other.m_Size;
        m_Buffer = new char[m_Size + 1];
        memcpy(m_Buffer, other.m_Buffer, m_Size + 1);

        copy_count++;
    }



    // Move constructor
    // String(String&& other) noexcept{
    //     //Following code does moving!
    //     std::cout << "Move constructor of String class invoked." << std::endl;
    //     m_Size = other.m_Size;
    //     m_Buffer = other.m_Buffer; //Pointing to the existing block of data
    
    //     //BUT THERE'S A PROBLEM
    //     //Since there are two string instances and if the memory block is can be freed
    //     // by both instances (and hence will result in seg. fault due to double free)

    //     // HENCE:
    //     other.m_Size = 0;
    //     other.m_Buffer = nullptr;
    // }
};


class Person{
public:
    String person_name;

    Person(const String& name):person_name(name){
        std::cout << "Person created from String lvalue" << std::endl;
    }

    //This forces invocation of move constructor
    // Person(String&& name):person_name((String&&) name){
    //     std::cout << "Person created from temporary." << std::endl;
    // }

    void PrintName(){
        std::cout << "Person name is " << person_name << "." << std::endl;
    }

};

 void DisplayString(String str){
    std::cout << "DISPLAYING STRING : " << str << std::endl;
}


void DisplayStringV2(String& str){
   std::cout << "DISPLAYING STRING VALUE: " << str << std::endl;
}

// void DisplayStringV2(String&& str){
//     std::cout << "DISPLAYING STRING RVALUE : " << str << std::endl;
// }


int main(){
    // Copy constructor makes sure that we actually make allocate different memory
    // space allocated to store the actual string of characters 
    Person p1 = Person(String("Ram"));
    p1.PrintName();
    
    // Why is copy created!??
    // Can't we directly assign String("Gopal") to p1.person_name()
    
    // Here a throwaway object i.e. String("Gopal") is created on the current scope's stack frame.
    // We don't need it here, we need it inside that function but we need to create here and pass the copy
}