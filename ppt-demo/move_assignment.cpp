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
        if (string.m_Size > 0)
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
    String(String&& other) noexcept{
        //Following code does moving!
        std::cout << "Move constructor of String class invoked." << std::endl;
        m_Size = other.m_Size;
        m_Buffer = other.m_Buffer; //Pointing to the existing block of data
    
        //BUT THERE'S A PROBLEM
        //Since there are two string instances and if the memory block is can be freed
        // by both instances (and hence will result in seg. fault due to double free)

        // HENCE:
        other.m_Size = 0;
        other.m_Buffer = nullptr;
    }

    String& operator=(String&& other) noexcept{
        // Everything else is same, except, we will need to remove the content of
        // existing object that is already created.

        std::cout << "Move Assignment of String class invoked." << std::endl;

        if (this != &other){

            delete[] m_Buffer; 
            // (Make sure source and destinaiton are not same while moving, otherwise we wil kill the data)

            //Following code does moving!        
            m_Size = other.m_Size;
            m_Buffer = other.m_Buffer; //Pointing to the existing block of data

            // Clears the old object (Makes hollow object)
            other.m_Size = 0;
            other.m_Buffer = nullptr;
        }

        return *this;
    }
};

void DisplayStringV2(String& str){
   std::cout << "DISPLAYING STRING VALUE: " << str << std::endl;
}


int main(){
   
    String str1 = String ("Python");
    String str2 = (String&&) str1;  // Alternate way: String str3 = std::move(str1);

    
    //However we can't move on already existing objects by assigning
    String str3("C++");
    
    // We are not able to do this, until we define an move assignment
    str3 = std::move(str2);


    DisplayStringV2(str3);
    

    // We sucesfully transferred ownership without copying.

}