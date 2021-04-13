#include "zlist.hpp"

# include <iostream>

int main(int argc, char const *argv[])
{
    ZList<int> intlist;

    try
    {
        int first = intlist.first()
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    

}
