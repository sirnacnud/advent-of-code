#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


std::vector<int8_t> parseNumbersFromLine(const std::string& line, char separator) {
    std::stringstream ss(line);
    std::string s;

    std::vector<int8_t> numbers;
    while (getline(ss, s, separator)) {
        try {
            int8_t number = (uint8_t)stoi(s);
            numbers.push_back(number);
        } catch (const std::invalid_argument& e) {
            continue;        
        }
    }

    return numbers;
}

void printNumbers(const std::vector<int>& numbers) {
    for(size_t i = 0; i < numbers.size(); ++i) {
        std::cout << numbers[i] << ",";    
    }

    std::cout << std::endl;
}

void simulateFishPopulation(std::vector<int8_t>& fish, int days) {
    int remainingDays = days;

    while(remainingDays > 0) {
        std::cout << remainingDays << " Day - " << fish.size() << " fish" << std::endl;

        std::vector<int8_t> newFish;

        for (size_t i = 0; i < fish.size(); ++i) {
            fish[i] -= 1;

            if (fish[i] == -1) {
                fish[i] = 6;
                newFish.push_back(8);            
            }
        }    

        fish.insert(fish.end(), newFish.begin(), newFish.end());
    
        remainingDays -=1;    
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Supply input file as first argument" << std::endl;
        return -1;    
    }

    if (argc < 3) {
        std::cerr << "Supply number of days to simulate fish population as second argument" << std::endl;
        return -1;    
    }

    int daysToSimulate = atoi(argv[2]);

    std::ifstream inputFile;
    inputFile.open(argv[1]);

    if (inputFile.is_open()) {
        std::string line;

        std::vector<std::string> lines;
        while (getline(inputFile, line)) {
            lines.push_back(line);
        }

        std::vector<int8_t> fish = parseNumbersFromLine(lines[0], ',');

        simulateFishPopulation(fish, daysToSimulate);

        std::cout << fish.size() << std::endl;
    }
}
