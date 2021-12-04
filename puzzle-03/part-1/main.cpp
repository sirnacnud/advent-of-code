#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int convertBinaryStringToInt(const std::string& string) {
    int value = 0;
    size_t length = string.size();

    for (std::size_t i = 0; i < length; ++i) {
        if (string[i] == '1') {
            value |= 1 << (length - i - 1); 
        }
    }

    return value;
}

int calculatePowerConsumption(std::vector<int>& readings, int numberOfBits) {
    int gammaRate = 0;
    int epsilonRate = 0;

    for (std::size_t i = 0; i < numberOfBits; ++i) {
        int onesCount = 0;
        int zeroesCount = 0;

        int bitTest = 1 << (numberOfBits - i - 1);

        for (std::size_t j = 0; j < readings.size(); ++j) {
            if (readings[j] & bitTest) {
                onesCount++;            
            } else {
                zeroesCount++;
            }
        }

        if (onesCount > zeroesCount) {
            gammaRate |= bitTest;
        } else {
            epsilonRate |= bitTest;
        }
    }

    std::cout << "Gamma Rate: " << gammaRate << std::endl;
    std::cout << "Epsilon Rate: " << epsilonRate << std::endl;

    return gammaRate * epsilonRate;
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
        std::vector<int> readings;
        int numberOfBits = 0;

        while (getline(inputFile, line)) {
            numberOfBits = line.size();
            int reading = convertBinaryStringToInt(line);
            readings.push_back(reading);
        }

        int powerConsumption = calculatePowerConsumption(readings, numberOfBits);
        std::cout << "Power Consumption: " << powerConsumption << std::endl;
    }
}
