#include "myarray.h"

template <class T, int n>
Array<T, n>::Array(){
    cnt = 0;
} 

template <class T, int n >
Array<T, n>::Array(int m, const T& val ){
    cnt = m;
    for(int i=0; i < cnt; i++ )
        arr[i] = val;
}


template <class T, int n >
void Array<T, n>::append( T val) throw(OutOfRange){
    if( cnt < n)
       arr[cnt++] = val;
    else
        throw OutOfRange();
}
template <class T, int n >
void Array<T, n>::append( const Array<T,n>& v) throw(OutOfRange){
    if( cnt + v.cnt > n)
    // Not enough space.
        throw OutOfRange();
    int count = v.cnt;
    for( int i=0; i < count; ++i)
        arr[cnt++] = v.arr[i];
}

template <class T, int n >
void Array<T, n>::insert( T val, int pos) throw(BadIndex, OutOfRange){
    insert( Array<T,n>(1,val), pos);
}

template <class T, int n >
void Array<T, n>::insert( const Array<T,n>& v, int pos ) throw(BadIndex, OutOfRange){
    if( pos < 0 || pos >= cnt)
        throw BadIndex();
    // Invalid position.
    if( n < cnt + v.cnt)
        throw OutOfRange();
    int i;

    for( i = cnt-1; i >= pos; --i)  // Shift up
        arr[i+v.cnt] = arr[i];      // starting at pos.


    for( i = 0; i < v.cnt; ++i)
        arr[i+pos] = v.arr[i];
    cnt = cnt + v.cnt; // Fill the gap.
}

template <class T, int n >
void Array<T, n>::remove(int pos) throw(BadIndex){
    if( pos >= 0 && pos < cnt){
        for( int i = pos; i < cnt-1; ++i)
           arr[i] = arr[i+1];
        --cnt;
    }else
        throw BadIndex(pos);
}

template <class T, int n >
ostream& operator<<(ostream& os, const Array<T,n>& v){
    int w = os.width();
    // Save the field width
    for( int i = 0; i < v.cnt; ++i){
        os.width(w);
        os << v.arr[i];
    }
    os << endl;
    return os;
}