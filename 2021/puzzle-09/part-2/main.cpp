#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<int> parseNumbersFromString(const std::string& string) {
    std::vector<int> numbers;

    for (size_t i = 0; i < string.size(); ++i) {
        try {
            char character = (string[i]);
            int number = atoi(&character);
            numbers.push_back(number);
        } catch (const std::invalid_argument& e) {
            continue;        
        }
    }

    return numbers;
}

int findBasinSize(const std::vector<std::vector<int>>& heatmap, std::vector<std::vector<bool>>& checkedMap, int r, int c) {
    if (checkedMap[r][c] == true) {
        return 0;
    }    

    checkedMap[r][c] = true;

    if (heatmap[r][c] == 9) {
        return 0;    
    }    

    int count = 1;

    // Check top
    if (r > 0) {
        count += findBasinSize(heatmap, checkedMap, r - 1, c);
    }

    // Check left
    if (c > 0) {
        count += findBasinSize(heatmap, checkedMap, r, c - 1);
    }

    // Check right
    if (c < heatmap[r].size() - 1) {
        count += findBasinSize(heatmap, checkedMap, r, c + 1);  
    }

    // Check bottom
    if (r < heatmap.size() - 1) {
        count += findBasinSize(heatmap, checkedMap, r + 1, c);
    }

    return count;
}

int calculateSizeOfBasins(const std::vector<std::vector<int>>& heatmap) {
    std::vector<int> basins;

    std::vector<std::vector<bool>> checkedMap;
    for (size_t r = 0; r < heatmap.size(); ++r) {
        std::vector<bool> newRow;
        for (size_t c = 0; c < heatmap[r].size(); ++c) {
            newRow.push_back(false);
        }
        checkedMap.push_back(newRow);
    }

    for(size_t r = 0; r < heatmap.size(); ++r) {
        for(size_t c = 0; c < heatmap[r].size(); ++c) {
            int value = heatmap[r][c];

            // Check top
            if (r > 0) {
                if (heatmap[r - 1][c] <= value) {
                    continue;              
                }
            }

            // Check left
            if (c > 0) {
                if (heatmap[r][c - 1] <= value) {
                    continue;                
                }            
            }

            // Check right
            if (c < heatmap[r].size() - 1) {
                if (heatmap[r][c + 1] <= value) {
                    continue;
                }            
            }

            // Check bottom
            if (r < heatmap.size() - 1) {
                if (heatmap[r + 1][c] <= value) {
                    continue;                
                }            
            }

            // Found low point, calculate basin
            int basin = findBasinSize(heatmap, checkedMap, r, c);
            basins.push_back(basin);
        }
    }

    std::sort(basins.rbegin(), basins.rend());

    return basins[0] * basins[1] * basins[2];
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
        
        std::vector<std::vector<int>> heatmap;

        while (getline(inputFile, line)) {
            std::vector<int> numbers = parseNumbersFromString(line);
            heatmap.push_back(numbers);
        }

        int size = calculateSizeOfBasins(heatmap);
        std::cout << size << std::endl;
    }
}
