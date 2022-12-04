#include <iostream>
#include <fstream>
#include <string>
#include <vector>

const int MAX_ELVES = 3;

void updateMaxCalories(std::vector<int>& maxCalories, int calories) {
    if (maxCalories.empty()) {
        maxCalories.push_back(calories);    
    } else {
        for (auto iter = maxCalories.begin(); iter != maxCalories.end(); ++iter) {
            if (calories > *iter) {
                maxCalories.insert(iter, calories);
                break;            
            }
        }

        if (maxCalories.size() > MAX_ELVES) {
            maxCalories.pop_back();        
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Supply input file as first argument" << std::endl;
        return -1;    
    }

    std::ifstream inputFile;
    inputFile.open(argv[1]);

    std::vector<int> maxCalories;

    if (inputFile.is_open()) {
        std::string inputLine;

        int calories = 0;

        while (getline(inputFile, inputLine)) {
            // Next elf detected
            if (inputLine == "") {
                updateMaxCalories(maxCalories, calories);
                calories = 0;
            } else {
                try {
                    int amount = stoi(inputLine);
                    calories += amount;
                } catch (const std::invalid_argument& e) {
                    continue;            
                }
            }
        }

        updateMaxCalories(maxCalories, calories);

        int totalCalories = 0;
        for (size_t i = 0; i < MAX_ELVES; ++i) {
            totalCalories += maxCalories[i];
        }

        std::cout << totalCalories << std::endl;
    }
}
