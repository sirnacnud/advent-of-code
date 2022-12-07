#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <vector>

void convertToItems(std::set<char>& items, const std::string& rucksack) {
    size_t size = rucksack.size();

    for(size_t i = 0; i < size; ++i) {
        items.insert(rucksack[i]);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Supply input file as first argument" << std::endl;
        return -1;    
    }

    std::ifstream inputFile;
    inputFile.open(argv[1]);

    if (inputFile.is_open()) {
        std::string inputLine;

        std::vector<std::string> rucksacks;

        while (getline(inputFile, inputLine)) {
            rucksacks.push_back(inputLine);
        }

        size_t groupCount = rucksacks.size() / 3;
        int ruckSackIndex = 0;

        std::vector<char> badges;
        std::set<char> setOne;
        std::set<char> setTwo;
        std::set<char> setThree;

        for (size_t i = 0; i < groupCount; ++i) {
            convertToItems(setOne, rucksacks[ruckSackIndex]);
            convertToItems(setTwo, rucksacks[ruckSackIndex + 1]);
            convertToItems(setThree, rucksacks[ruckSackIndex + 2]);

            for (auto iter = setOne.begin(); iter != setTwo.end(); ++iter) {
                char item = *iter;

                std::set<char>::iterator iterTwo = setTwo.find(item);
                std::set<char>::iterator iterThree = setThree.find(item);

                if (iterTwo != setTwo.end() && iterThree != setThree.end()) {
                    badges.push_back(item);
                    break;
                } 
            }

            setOne.clear();
            setTwo.clear();
            setThree.clear();
            ruckSackIndex += 3;
        }

        int sum = 0;

        for (auto iter = badges.begin(); iter != badges.end(); ++iter) {
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
