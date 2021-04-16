#include "zlist.hpp"

# include <iostream>

int main(int argc, char const *argv[])
{
    ZList<int> intlist;
    intlist.append(10);
    ZList<int> sec_list(20, &intlist);
    ZList<int> latest(50, &sec_list);
    std::cout << "The last element is " << latest.last() << std::endl;

    for (int i = 0; i<latest.size(); i++){
        std::cout << "apple = " << *(latest.ptr+i) << std::endl;
    }

}
