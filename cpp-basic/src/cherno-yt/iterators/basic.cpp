#include <iostream>
#include <vector>
#include <unordered_map>

int main(){
    std::vector<int> values = {1, 2, 3, 4, 5};

    for (std::vector<int>::iterator it = values.begin(); it != values.end(); it++){
        std::cout << *it << std::endl;
    }

    for (auto& v: values){
        std::cout << v << std::endl;
    }

    std::unordered_map<std::string, int> map;
    map["Madhav"] = 28;
    map["Steve"] = 73;

    for (std::unordered_map<std::string, int>::const_iterator it = map.begin(); it != map.end(); it++){
        std::cout << it->first << " => " << it->second << std::endl;
    }

    for (auto kv : map){
        std::cout << kv.first << " => " << kv.second << std::endl;
    }

    for (auto [k, v] : map){ //needs c++17 for structured bindings
        std::cout << "key = " << k << " and value = " << v << std::endl;
    }

    return 0;
}
