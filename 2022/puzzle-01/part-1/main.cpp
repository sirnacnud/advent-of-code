#include <iostream>
#include <fstream>
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

        int calories = 0;
        int maxCalories = 0;

        while (getline(inputFile, inputLine)) {
            // Next elf detected
            if (inputLine == "") {
                if (calories > maxCalories) {
                    maxCalories = calories;                
                }

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

        if (calories > maxCalories) {
            maxCalories = calories;                
        }

        std::cout << maxCalories << std::endl;
    }
}
