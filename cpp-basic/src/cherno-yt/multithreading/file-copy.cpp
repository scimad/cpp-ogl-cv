#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <cctype>
#include <future>
#include <chrono>
#include <any>

class SimpleTimer
{
public:
    std::chrono::time_point<std::chrono::high_resolution_clock> begin, end;
    SimpleTimer(/* args */){
        begin = std::chrono::high_resolution_clock::now();
    };
    ~SimpleTimer(){
        std::chrono::duration<int, std::micro> d;
        d = get_duration();
        std::cout << "The timer lived for " << d.count() << " micro." << std::endl;
    };

    std::chrono::duration<int, std::micro> get_duration(){
        return std::chrono::duration_cast<std::chrono::duration<int, std::micro>>(std::chrono::high_resolution_clock::now()-begin);
    }

};


bool read_and_rewrite_txt(std::string file_path){
    bool scrambled = false;
    if (std::filesystem::is_regular_file(file_path)){
        std::string ext = file_path.substr(file_path.find_last_of('.'),4);
        //lambda to convert string to lower
        [](std::string& exten){
            for (auto& s : exten)
                s = tolower(s);
        }(ext);
        if (ext.compare(".txt") == 0){
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
                w.open(folder_path + "scrambled_" +  filename + ".xtx");
                if (w.is_open()){
                    w.write(new_str.c_str(),sizeof(char)*new_str.length());
                }
                w.close();
                scrambled = true;
            }
        }
    }
    return scrambled;
}

int main(int argc, char* argv[]){
    if (argc<2){
        std::cout << "Enter folder name with txt files" << std::endl;
        return 0;
    }
    
    const std::string folder_path = std::string(argv[1]);
    {
        int n_files = 0;
        SimpleTimer T;
        for (const auto& entry : std::filesystem::directory_iterator(folder_path)){
            std::string filename = entry.path();
            std::future<bool> success = std::async(std::launch::async, read_and_rewrite_txt, filename);
            if (success.get()){
                std::cout << "Scrambling " << filename << std::endl;
                n_files++;
            }
        }
        if (n_files != 0)
            std::cout << "average time for each file = " <<  T.get_duration().count() / n_files << std::endl;//.count() / n_files;
    }
    std::cout << "-----------------------------" << std::endl;
    {
        int n_files = 0;
        SimpleTimer T;
        for (const auto& entry : std::filesystem::directory_iterator(folder_path)){
            std::string filename = entry.path();
            if (read_and_rewrite_txt(filename)){
                std::cout << "Scrambling " << filename << std::endl;
                n_files++;
            }
        }
        if (n_files != 0)
            std::cout << "average time for each file = " <<  T.get_duration().count() / n_files << std::endl;//.count() / n_files;
    }
    return 0;
}
