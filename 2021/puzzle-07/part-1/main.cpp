#include <iostream>
#include <fstream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

std::vector<int> parseNumbersFromLine(const std::string& line, char separator) {
    std::stringstream ss(line);
    std::string s;

    std::vector<int> numbers;
    while (getline(ss, s, separator)) {
        try {
            int number = stoi(s);
            numbers.push_back(number);
        } catch (const std::invalid_argument& e) {
            continue;        
        }
    }

    return numbers;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Supply input file as first argument" << std::endl;
        return -1;    
    }

    std::ifstream inputFile;
    inputFile.open(argv[1]);

    if (inputFile.is_open()) {
        std::string line;

        if (getline(inputFile, line)) {
            std::vector<int> crabs = parseNumbersFromLine(line, ',');

            int maxPosition = 0;
            int minPosition = std::numeric_limits<int>::max();

            for (size_t i; i < crabs.size(); ++i) {
                maxPosition = std::max(maxPosition, crabs[i]);
                minPosition = std::min(minPosition, crabs[i]);        
            }

            int minimumFuelCost = std::numeric_limits<int>::max();

            for (int p = minPosition; p <= maxPosition; ++p) {
                int fuelCost = 0;
                for (size_t i = 0; i < crabs.size(); ++i) {
                    fuelCost += (std::abs(crabs[i] - p));                
                }

                if (fuelCost < minimumFuelCost) {
                    minimumFuelCost = fuelCost;                
                }
            }

            std::cout << "Minimum fuel cost to align: " << minimumFuelCost << std::endl;
        }
    }
}
