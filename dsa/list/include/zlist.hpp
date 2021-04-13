template <typename T>
class ZList{
    int _size;
    int _max_size;
    T* ptr;
public:
    ZList();
    ZList(T element, ZList<T>* list);

    ~ZList();
    int size(){
        return _size;
    };

   T first();
   //ZList<T> rest();
   //bool IsEmptyList();
   //void replaceFirst(T newElement);
   //void replaceRest(ZList<T> newList);
};
