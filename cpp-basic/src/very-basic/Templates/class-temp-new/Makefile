all:

	g++ -c myarray.cpp -fPIC
	g++ -shared -o libarr.so myarray.o -fPIC
	g++ -o main Array_t.cpp -larr -L./ -fPIC

clean:
	rm *.o *.so main

