# Notes from chapter 24: Type Conversion in Class Hierarchies


## Implicit Type Conversions

Type conversions that walk up a class hierarchy i.e. conversions from derived to base class objects, reference, pointers are always safe. Upcasting is performed implicitly for this reason.


* Implicit casting objects, pointers and references from derived class to base class is possible as the principle is "more can always fill the less"

* The members / methods of derived classed cannot be accessed in objects, reference , pointers of base classes because only the generic terms (members defined in base class) are copied.

* Assignment or trying to implicit conversion of base class object , reference, pointer to derived class isn't valid as it will leave some of the members of the derived class empty.

## Explicit Type Conversions

Type conversions that involve walking down the tree, or downcasts i.e. conversions from base to derived class objects, reference, pointers can only be performed explicitly by means of cast construction. The cast operator (type) [eg, (int) 3.14], which was available in C, or the static_cast<type> operator are available for this task.

