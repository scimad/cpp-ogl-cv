#include <iostream>
#include <vector>
using namespace std;
int main(){
	vector <int> v {1, 2, 3, 4, 5};
	vector <int>::iterator itr;
	for (itr = v.begin(); itr != v.end(); itr ++){
		std::cout << "The value is " << *itr << endl;

	}

}
