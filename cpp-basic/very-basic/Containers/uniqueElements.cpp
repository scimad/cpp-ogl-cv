#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
void solve();
int main(){
    solve();
}

void solve(){
    vector <char> v {'m', 'a', 'd', 'h','a','v'};
    std::cout << v.size() << std::endl;
    std::unordered_map<char, int> char_index;
    int k = 0;
    for (size_t i = 0; i < v.size(); i++){
        std::cout << "Checking for element " << v.at(i) << std::endl;
        if (char_index.find(v.at(i)) == char_index.end()){
            char_index[v.at(i)] = i;
            v[(size_t)k] = v.at(i);
            k++;
        }
    }
    v.resize(k);
    std::cout << "Printing Unique" <<std::endl;
    for (const auto& c: v){
        std::cout << c << std::endl;
    }
}
