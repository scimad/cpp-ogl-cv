#include<iostream>
#include<array>
#include<string>

void* operator new(size_t size){
    void* ptr = malloc(size);
    std::cout << "[" << size << " Bytes] allocated on heap at location:" << ptr << std::endl;
    return ptr;
}


void operator delete(void* ptr){
    free(ptr);
    std::cout << "Memory freed from heap at location:" << ptr << std::endl;
}

template <typename T, size_t size>
class MyArray{
private:
    T m_Data[size];
public:
    MyArray(T initial){
        for (size_t i=0; i < size; i++){
            m_Data[i] = initial;
        }
    };
    size_t Size(){
        return size;
    }

    T& operator[](size_t pos){
        return m_Data[pos];
    }


    T at(size_t pos){
        return m_Data[pos];
    }
    ~MyArray(){

    };
};

int main(){

    //stack based c-style array
    int num[5]={}; //memset 0
    for (int i=0; i<5; i++){
        std::cout << num[i] << std::endl;
    }

    //heap based c-style array
    int* h_Num = new int[5];
    for (int i=0; i<5; i++){
        std::cout <<h_Num[i] << std::endl;
    }
    delete h_Num;

    std::cout << "Hit Enter key to continue..";
    std::cin.get();
    //cpp-style array
    std::array<std::string, 5> stdarray;
    stdarray[0]= "Madhav";
    stdarray[4] = "Humagain";

    for (auto& str : stdarray){
        std::cout << str << std::endl;
    }

    std::cout << "Hit Enter key to continue..";
    std::cin.get();

    //custom array
    MyArray<std::string, 5> m_array("Madhav");

    for (int i=0; i<5; i++){
        std::cout << m_array.at(i) << std::endl;
        m_array[i] = std::string("Nepal");
        std::cout << m_array.at(i) << std::endl;

    }

    std::cout << "Hit Enter key to exit.";
    std::cin.get();


    return 0;
}
