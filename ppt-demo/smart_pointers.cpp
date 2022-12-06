#include <iostream>
#include <memory>

// Leaking memory example
// #include <iostream>
// using namespace std;
 
// class Rectangle {
// private:
//     int length;
//     int breadth;
// };
 
// void fun()
// {
//     // By taking a pointer p and
//     // dynamically creating object
//     // of class rectangle
//     Rectangle* p = new Rectangle();
//     // Do something with this rectangle
// }
 
// int main()
// {
//     // Infinite Loop
//     while (1) {
//         fun();
//     }
// }


class TestClass{
private:
    std::string my_name;
public:
    TestClass(std::string name):my_name(name)
    {
        std::cout << "Object created with name " << my_name << std::endl;
    };
    ~TestClass()
    {
        std::cout << "Destroyed object with name " << my_name << std::endl;
    };
    void setName(std::string name){
        std::cout << "Setting name: " << name << std::endl;

        if (this)
        {
        std::cout << "Name changed from " << my_name << " to " << name << std::endl;
        my_name = name;
        }else{
            std::cout << "Can't write the name \"" << name <<  "\" as the object you're trying to write into is already dead." << std::endl;
        }

    }
};


int main(int argc, char const *argv[])
{
    {
        std::shared_ptr<TestClass> s_ptr;
        {
            auto s2_ptr = std::make_shared<TestClass>("Madhav"); //returns std::shared_ptr
            s2_ptr->setName("Ram");
            auto s_ptr = s2_ptr;
        }
        s_ptr->setName("Hari");
    }

    {
        std::unique_ptr<TestClass> u_ptr;
        {
            auto u2_ptr = std::make_unique<TestClass>("Apple");
            u_ptr = std::make_unique<TestClass>("Ball");
        }
        u_ptr->setName("Cat");
    }

    {
        auto s_ptr= std::make_shared<TestClass>("Kapuri");
        std::weak_ptr<TestClass> w_ptr = s_ptr; //w_ptr doesn't take ownership of Kapuri
        s_ptr->setName("Kharayo");
        std::cout << "Ref count = " << s_ptr.use_count() << std::endl;

        {
            auto p = w_ptr.lock();  //p takes the ownership of Kapuri, ref count is increased
            std::cout << "Ref count = " << s_ptr.use_count() << std::endl;
        }   //p is destroyed and refcount of Kapuri (now Kharayo) is decreased

        std::cout << "Ref count = " << s_ptr.use_count() << std::endl;
    }
}
