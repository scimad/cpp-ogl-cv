template <typename T>
class Zlist{
    T* ptr;
public:
    Zlist();
    Zlist(T element, Zlist<T> list);
   //~Zlist();
   //T first();
   //Zlist<T> rest();
   //bool IsEmptyList();
   //void replaceFirst(T newElement);
   //void replaceRest(Zlist<T> newList);
};
