#include <bitset>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void printBitset(std::vector<std::bitset<1>>& bitset) {
    for (std::size_t i = 0; i < bitset.size(); ++i) {
        std::cout << bitset[i];
    }

    std::cout << std::endl;
}

std::vector<std::bitset<1>> convertStringToBinary(const std::string& string) {
    std::vector<std::bitset<1>> bitsets;
    for (std::size_t i = 0; i < string.size(); ++i) {
        bitsets.push_back(std::bitset<1>(string[i]));
    }

    return bitsets;
}

int convertBitsetToInt(std::vector<std::bitset<1>>& bitset) {
    int value = 0;

    for (std::size_t i = 0; i < bitset.size(); ++i) {
        if (bitset[i] == 1) {
            value |= 1 << (bitset.size() - i - 1);        
        }
    }

    return value;
}

int calculatePowerConsumption(std::vector<std::vector<std::bitset<1>>>& readings) {
    
    std::vector<std::bitset<1>> gammaRate;
    std::vector<std::bitset<1>> epsilonRate;

    int index = 0;

    for (std::size_t i = 0; i < readings[index].size(); ++i) {
        int onesCount = 0;
        int zeroesCount = 0;

        for (std::size_t j = 0; j < readings.size(); ++j) {
            if (readings[j][index][0] == 0) {
                zeroesCount++;            
            } else {
                onesCount++;
            }
        }

        if (onesCount > zeroesCount) {
            gammaRate.push_back(std::bitset<1>(1));
            epsilonRate.push_back(std::bitset<1>(0));
        } else {
            gammaRate.push_back(std::bitset<1>(0));
            epsilonRate.push_back(std::bitset<1>(1));
        }

        index++;
    }

    printBitset(gammaRate);
    printBitset(epsilonRate);

    int gammaValue = convertBitsetToInt(gammaRate);
    int epsilonValue = convertBitsetToInt(epsilonRate);

    std::cout << gammaValue << std::endl;
    std::cout << epsilonValue << std::endl;

    return gammaValue * epsilonValue;
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

        std::vector<std::vector<std::bitset<1>>> readings;

        while (inputFile.good()) {
            inputFile >> line;
            std::vector<std::bitset<1>> reading = convertStringToBinary(line);
            readings.push_back(reading);
        }

        int powerConsumption = calculatePowerConsumption(readings);
        std::cout << powerConsumption << std::endl;
    }
}
