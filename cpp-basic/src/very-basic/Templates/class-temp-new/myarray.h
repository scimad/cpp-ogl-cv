#ifndef _ARRAY_H_
#define _ARRAY_H_
#include <iostream>
#include <iomanip>
using namespace std;
class BadIndex{
	private:
	int index;
	
	public:
	BadIndex(int i):index(i){}
	int getBadIndex() const { return index; }
};

class OutOfRange {/* Without data members*/ };

template <class T, int n=256>
class Array
{
	private:
	T arr[n]; // The array
	int cnt; // Current number of elements
	
	public:
	Array();
	Array(int m, const T& val );
	int length() const { return cnt; }
	int size() const { return n; }

	T& operator[](int i) throw(BadIndex){
		if( i < 0 || i >= cnt ) throw BadIndex(i);
		return arr[i];
	}
	
	const T& operator[](int i) const throw(BadIndex){
		if( i < 0 || i >= cnt ) throw BadIndex(i);
		return arr[i];
	}

	Array& operator+=( float val) throw(OutOfRange){
		append( val);
		return *this;
	}
	Array& operator+=(const Array& v) throw(OutOfRange){
		append(v);
		return *this;
	}

	void append( T val) throw(OutOfRange);
	void append( const Array& v) throw(OutOfRange);
	void insert( T val, int pos) throw(BadIndex, OutOfRange);
	void insert( const Array& v, int pos ) throw(BadIndex, OutOfRange);
	void remove(int pos) throw(BadIndex);
};

#endif
