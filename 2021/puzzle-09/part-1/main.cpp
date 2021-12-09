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

int calculateRiskLevel(const std::vector<std::vector<int>>& heatmap) {
    int level = 0;

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

            // Found low point
            level += (1 + value);
        }    
    }

    return level;
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

        int level = calculateRiskLevel(heatmap);
        std::cout << level << std::endl;
    }
}
