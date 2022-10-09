#include <stddef.h>
#include <stdlib.h>
#include <iostream>
#include "custom-alloc.hpp"

int main(){
	int* num = new int();

	int* num_list = new int[10];

	*num = 100;
	std::cout << "a = " << *num << std::endl;

	for (int i=0; i<10; i++){
		num_list[i] = i;
	}

	delete num;
	delete[] num_list;

}