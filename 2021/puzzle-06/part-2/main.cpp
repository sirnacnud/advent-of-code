#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

const int MAX_NUMBER_FISH_GROUPS = 9;

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

uint64_t simulateFishPopulation(std::vector<int>& fish, int days) {
    int remainingDays = days;

    uint64_t fishCounts[MAX_NUMBER_FISH_GROUPS] = {};
    uint64_t newFishCounts[MAX_NUMBER_FISH_GROUPS] = {};

    for (size_t i = 0; i < fish.size(); ++i) {
        switch (fish[i]) {
        case 0:
            fishCounts[0] +=1;
            break;
        case 1:
            fishCounts[1] += 1;
            break;
        case 2:
            fishCounts[2] += 1;
            break;
        case 3:
            fishCounts[3] += 1;
            break;
        case 4:
            fishCounts[4] += 1;
            break;
        case 5:
            fishCounts[5] += 1;
            break;
        case 6:
            fishCounts[6] += 1;
            break;
        case 7:
            fishCounts[7] += 1;
            break;
        case 8:
            fishCounts[8] += 1;
            break;
        }
    }

    while(remainingDays > 0) {
        for (int i = 8; i >= 0; --i) {
            if (i == 0) {
                newFishCounts[8] = fishCounts[0];
                newFishCounts[6] += fishCounts[0];
            } else {
                newFishCounts[i - 1] = fishCounts[i];
            }
        }
    
        memcpy(&fishCounts, &newFishCounts, sizeof(uint64_t) * MAX_NUMBER_FISH_GROUPS);

        remainingDays -=1;    
    }

    uint64_t totalFish = 0;
    for (int i = 0; i < MAX_NUMBER_FISH_GROUPS; ++i) {
        totalFish += fishCounts[i];    
    }

    return totalFish;
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

    std::ifstream inputFile;
    inputFile.open(argv[1]);

    if (inputFile.is_open()) {
        std::string line;

        if (getline(inputFile, line)) {
            std::vector<int> fish = parseNumbersFromLine(line, ',');

            int daysToSimulate = atoi(argv[2]);
            uint64_t totalFish = simulateFishPopulation(fish, daysToSimulate);

            std::cout << totalFish << std::endl;
        }
    }
}
