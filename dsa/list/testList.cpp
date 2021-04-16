#include "zlist.hpp"

# include <iostream>

int main(int argc, char const *argv[])
{
    ZList<int> intlist;
    intlist.replaceFirst(10);
    ZList<int> sec_list(20, &intlist);
    ZList<int> latest(50, &sec_list);
    ZList<int> rest = latest.rest();
    int last = latest.last();
    std::cout << "The last element is " << last << std::endl;

}
