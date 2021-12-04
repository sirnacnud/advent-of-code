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

enum Rating {
    oxygenGeneratorRating,
    c02ScrubberRating
};

int calculateRating(std::vector<int> readings, int numberOfBits, Rating rating) {
    std::vector<int> remainingReadings = readings;

    for (std::size_t i = 0; i < numberOfBits; ++i) {
        int onesCount = 0;
        int zeroesCount = 0;

        int bitTest = 1 << (numberOfBits - i - 1);

        for (std::size_t j = 0; j < remainingReadings.size(); ++j) {
            if (remainingReadings[j] & bitTest) {
                onesCount++;            
            } else {
                zeroesCount++;
            }
        }

        switch (rating) {
        case oxygenGeneratorRating:
            if (onesCount >= zeroesCount) {
                std::erase_if(remainingReadings, [bitTest](int x) { return ((x & bitTest) == 0); });
            } else {
                std::erase_if(remainingReadings, [bitTest](int x) { return ((x & bitTest) != 0); });
            }
            break;
        case c02ScrubberRating:
            if (onesCount < zeroesCount) {
                std::erase_if(remainingReadings, [bitTest](int x) { return ((x & bitTest) == 0); });
            } else {
                std::erase_if(remainingReadings, [bitTest](int x) { return ((x & bitTest) != 0); });
            }
            break;
        }
    }

    return remainingReadings[0];
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

        Rating oxygenRating = oxygenGeneratorRating;
        int oxygenGeneratorRating = calculateRating(readings, numberOfBits, oxygenRating);

        Rating c02Rating = c02ScrubberRating;
        int c02ScrubberRating = calculateRating(readings, numberOfBits, c02Rating);

        std::cout << "Oxygen Generator Rating: " << oxygenGeneratorRating << std::endl;
        std::cout << "C02 Scrubber Rating: " << c02ScrubberRating << std::endl;
        std::cout << "Life Support Rating: " << oxygenGeneratorRating * c02ScrubberRating << std::endl;
    }
}
