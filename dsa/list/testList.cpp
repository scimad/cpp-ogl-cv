#include "zlist.hpp"

# include <iostream>

int main(int argc, char const *argv[])
{
    ZList<int> intlist;

    std::cout << "Size of Rest is " << intlist.rest().size() << std::endl;
    intlist.replaceFirst(10);
    std::cout << "Size of intlist is " << intlist.size()<< std::endl;

    // try
    // {
    //     int first = intlist.first();
    // }
    // catch(const std::exception& e)
    // {
    //     std::cerr << e.what() << '\n';
    // }
    

}
