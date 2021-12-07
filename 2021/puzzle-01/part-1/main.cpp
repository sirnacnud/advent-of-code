#include <iostream>
#include <fstream>
#include <limits>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Supply input file as first argument" << std::endl;
        return -1;    
    }

    std::ifstream inputFile;
    inputFile.open(argv[1]);

    if (inputFile.is_open()) {
        std::string inputLine;

        int increases = 0;
        int previousReading = std::numeric_limits<int>::max();

        while (getline(inputFile, inputLine)) {
            try {
                int reading = stoi(inputLine);
                if (reading > previousReading) {
                    increases += 1;                
                }

                previousReading = reading;
            } catch (const std::invalid_argument& e) {
                continue;            
            }
        }

        std::cout << increases << std::endl;
    }
}
