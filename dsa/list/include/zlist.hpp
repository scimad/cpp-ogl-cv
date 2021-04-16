template <typename T>
class ZList{
    int _size;

public:
    T* ptr;
    ZList();
    ZList(const ZList<T>&);
    ZList(T element, ZList<T>* list);

    ~ZList();
    int size() const{
        return _size;
    };

   T first() const;
   ZList<T> rest() const;
   bool IsEmptyList() const;
   void replaceFirst(T newElement);
   T last() const;
   void append(ZList<T> list);
   void append(T element);
   //void replaceRest(ZList<T> newList);
};
