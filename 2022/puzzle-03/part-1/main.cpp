#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Supply input file as first argument" << std::endl;
        return -1;    
    }

    std::ifstream inputFile;
    inputFile.open(argv[1]);

    if (inputFile.is_open()) {
        std::string inputLine;

        std::set<char> items;
        std::vector<char> commonItems;

        while (getline(inputFile, inputLine)) {
            size_t length = inputLine.size();
            size_t half = length / 2;

            for (size_t i = 0; i < half; ++i) {
                items.insert(inputLine[i]);
            }

            for (size_t i = half; i < length; ++i) {
                std::set<char>::iterator result = items.find(inputLine[i]);
                if (result != items.end()) {
                    commonItems.push_back(inputLine[i]);
                    break;              
                }         
            }

            items.clear();
        }

        int sum = 0;

        for (auto iter = commonItems.begin(); iter != commonItems.end(); ++iter) {
            char item = *iter;

            if (item >= 'A' && item <= 'Z') {
                sum += item - 38;        
            } else {
                sum += item - 96;       
            }   
        }

        std::cout << sum << std::endl;
    }
}
