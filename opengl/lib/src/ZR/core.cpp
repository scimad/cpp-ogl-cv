#include <ZR/core.hpp>

namespace zr{
	void log(std::string message){
		/* TODO:
			* implement verbosity level and implement 
		*/ 
		std::cout << "\033[0;35m" << "[ZR] " "\033[1;32m" << message << "\033[0m" << std::endl;
	}
}