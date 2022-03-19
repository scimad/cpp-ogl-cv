all:

	g++ -c Account.cpp
	g++ -shared -o libAcc.so Account.o
	g++ -o main main.cpp -L. -lAcc
	# miracle@madhav:/src/$ LD_LIBRARY_PATH=. ./main
	# warning: Don't do `LD_LIBRARY_PATH=.` alone (but concat it with ./main)
clean:
	rm *.o *.so main

