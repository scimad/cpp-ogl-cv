// Containers
/*
Author        : scimad2.71@gmail.com
Written       : Sat, Mar 12, 2022
Last Modified : Sat, Mar 12, 2022
*/
#include <iostream>
#include <map>
#include <string>
using namespace std;

int main(int argc, char const *argv[]) {
  map<int, std::string> map_test = {
      pair<int, string>(1, "One"), pair<int, string>(2, "Two"),
      pair<int, string>(3, "Three"), pair<int, string>(0, "Zero")};

  for (auto i = map_test.begin(); i != map_test.end(); i++) {
    cout << i->first << " = " << i->second << endl;
  }

  return 0;
}
