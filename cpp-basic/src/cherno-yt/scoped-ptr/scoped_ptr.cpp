#include <iostream>

class TestClass
{
private:
    static int instance_id;
    int my_name = 0;
public:
    TestClass()
    {
        instance_id += 1;
        my_name = instance_id;
        std::cout << "Created a new object of type TestClass. (with name = "<<
         my_name << ")" << std::endl;

    };
    ~TestClass()
    {
        std::cout << "Destroyed object of type TestClass. (name = " <<
         my_name << ")" << std::endl;
    };
};

int TestClass::instance_id = 0;

class SmartPtr
{
private:
    TestClass* my_ptr;
public:
    SmartPtr(TestClass* t_ptr) : my_ptr(t_ptr)
    {
    }

    ~SmartPtr()
    {
        delete my_ptr;
    }
};

int main(int argc, char const *argv[])
{
    void* anyptr;
    {   //unnamed scope
        TestClass* tp_1 = new TestClass();
        TestClass* tp_2 = new TestClass();

        SmartPtr s_ptr1 = new TestClass(); //Implicit Conversion
        SmartPtr s_ptr2 = SmartPtr(new TestClass());

        anyptr = tp_2;

    }
    delete (TestClass*) anyptr;
    //Note that object associated with tp_1 doesn't get freed up and is managed
    //by OS after the program exits.
}
