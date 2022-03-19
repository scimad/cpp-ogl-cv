all:

	g++ -c Account.cpp
	g++ -shared -o libAcc.so Account.o
	g++ -o main main.cpp -lAcc -L./

clean:
	rm *.o *.so main

