# Notes from chapter 26: Abstract Classes

A class with pure virtual methods is an abstract class and a class derived from a class containing pure virtual methods is a concrete class, if it contains a definition for each pure virtual function.

* A NULL pointer is then entered in the virtual method table for the pure virtual method.

* If a class comprises pure virtual methods, you cannot create objects of this class type.

* An abstract class can still be derived from a concrete class, i.e. derived classes from a concrete class can contain pure virtual methods.

* An abstract class does not necessarily need to contain pure virtual functions.

* If the class contains a protected constructor, objects of the class type cannot be created. The constructor can only be called then by methods in derived classes. A constructor of
this type normally acts as base initializer.

## Pointers and References to Abstract Classes

TODO