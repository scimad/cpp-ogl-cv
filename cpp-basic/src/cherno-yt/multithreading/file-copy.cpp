#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <cctype>
#include <future>

void read_and_rewrite_txt(std::string file_path){
    if (std::filesystem::is_regular_file(file_path)){
        std::string ext = file_path.substr(file_path.find_last_of('.'),4);
        //lambda to convert string to lower
        [](std::string& exten){
            for (auto& s : exten)
                s = tolower(s);
        }(ext);
        if (ext.compare(".txt") == 0){
            std::cout << ".txt file found: " << file_path << std::endl;
            std::ifstream f;
            f.open(file_path);
            while (f.is_open()){
                std::string tp;
                std::string new_str;
                while (std::getline(f,tp)){
                    // std::cout << tp << std::endl;
                    new_str.append(
                        // lambda to reverse string
                        [](std::string t){
                            std::string new_str;
                            new_str.resize(t.length());
                            int i = 0;
                            for (auto& c : t){
                                i+=1;
                                new_str.at(new_str.length()-i) = c;
                            }
                            return new_str + "\n";
                        }(tp));
                }
                f.close();
                std::string folder_path = file_path.substr(0, file_path.find_last_of('/')+1);
                std::string filename = file_path.substr(file_path.find_last_of('/')+1);
                
                std::ofstream w;
                w.open(folder_path + "scrambled_" +  filename);
                if (w.is_open()){
                    w.write(new_str.c_str(),sizeof(char)*new_str.length());
                }
                w.close();
                std::cout << " File scrambled " << std::endl;
            }
        }
    }
}

int main(int argc, char* argv[]){
    if (argc<2){
        std::cout << "Enter folder name with txt files" << std::endl;
        return 0;
    }
    
    const std::string folder_path = std::string(argv[1]);

    for (const auto& entry : std::filesystem::directory_iterator(folder_path)){
        std::string filename = entry.path();
        read_and_rewrite_txt(filename);
        // std::async()

    }
    return 0;
}