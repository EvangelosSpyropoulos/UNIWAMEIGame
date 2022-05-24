#include "Engine.h"
#include <iostream>

void printUsage(ostream& os) {
    os << "Usage: UniWAMEIGame LEVELMAPFILE HIGHSCORESFILE " << std::endl;
}

int main(int argc, char** argv) {
    if (argc != 3) { 
        printUsage(std::cout);
        return 1;
    }
    
    Game::Engine engine(argv[1], argv[2]);
    return 0;
}
