#include <iostream>
using namespace std;

void square (int&);
int add (int&, int&);
int main(){
   int a = 55;
   int& b = a;

   cout << "b = " << b << endl;

   b = 22;

   cout << "a = " << a << endl;
   cout << "the sum is " << add (a, b) << endl;
   cout << "the square of " << a << " is ";
   square(a);
   cout << a << endl;
}

int add (int& a, int& b){
  return a + b;

}

void square(int& a /*const int& a //would return error when trying to modify*/){
  a *= a;
}
