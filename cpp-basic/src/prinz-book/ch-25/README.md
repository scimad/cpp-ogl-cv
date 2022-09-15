# Notes from chapter 25: Polymorphism


## Concept of Polymorphism

Most of the time, it makes sense to use pointers or references to the base class when special feature of derived class objects are insignificant. However, in cases such as in when the concrete object type will not be known until the program is executed, we still should be able to activate the special features of ta derived class.

The *object-oriented* approach to this problem is known as *polymorphism*. In C++, virtual methods are used to implement polymorphic classes.

* Redefinition of the derived class must have the same signature and the same return type as the virtual method in the base class

* The new version of the base class is automatically virtual itself.

* If the return type is a pointer or reference to the base class, the new version of the
virtual method can also return a pointer or reference to a derived class (Note:
Not all compilers support this option.)

* Constructors cannot have virtual declaration

## Destroying dynamically allocated objects

Dynamically created objects in a class hierarchy are normally handled by a base class pointer.

When dynamically created objects reaches the end of its lifetime and the memory occupied by the object is released by a *delete* statement, the destructor for the object is automatically called. If multiple constructors were called to create the object, the corresponding destructors are called in reverse order i.e. the destructor of the derived class is called first and then the destructor of the bse class is executed.

If multiple objects are dynamically created in the derived class, chances of unreferenced memory blocks being cluttered up in the main memory may occur if handled from base pointers which can be a dangerous situation. This can be solved by using virtual destructors.

## Static vs Dynamic binding

When a non-virtual method is called, the address of the function is known at compile time and the address is directly inserted into the machine code. Also if a virtual method is called via the object's name, the appropriate version of the method is also known at the compile time. Both of these cases are the case of *static* or *early binding*.

The opposite case, where the virtual method is called by a pointer or reference, the function that will be executed when the program is run is unknown at the time of compilation and the compiler is forced to create a machine code that does not form an association with a particular function until the program is run. This is referred to as *late* or *dynamic binding*.Dynamic binding is supported internally by virtual method tables.

Dynamic binding allows you to enhance compiled source code without having access to the source code. This is particularly important when you consider commercial class libraries, from which a user can derive his or her own classes and virtual function versions.

## Dynamic Casts

Use of *static_cast* can be unsafe during downcasts possibly resulting in fatal runtime errors. We can use *dynamic_cast* to mitigate the issue.

Given a pointer carPtr to the base class Car , the statement
Example: 

Truck* truckPtr = dynamic_cast<Truck*>(carPtr); 

performs a downcast to the derived Truck class, provided the pointer carPtr really
identifies a Truck type object. If this is not so, the dynamic_cast<Truck> operator
will return a NULL pointer.