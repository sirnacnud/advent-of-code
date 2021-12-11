#include <iostream>
#include <fstream>
#include <set>
#include <utility>

const int MAX_OCTOPUS_MAP_ROWS = 10;
const int MAX_OCTOPUS_MAP_COLUMNS = 10;

int** createArray(int rows, int columns) {   
    int** space = new int* [rows];

    for (size_t i = 0; i < rows; ++i) {
        space[i] = new int[columns];
    }

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            space[i][j] = 0;
        }
    }

    return space;
}

void freeArray(int** array, int rows) {
    for (size_t i = 0; i < rows; ++i) {
        delete[] array[i];    
    }

    delete[] array;
}

void printArray(int** array, int rows, int columns) {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            std::cout << array[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

void applyFlashIfNeeded(int** octopusMap, int r, int c, std::set<std::pair<int, int>>& flashedIndexes) {
    if (octopusMap[r][c] <= 9 || flashedIndexes.find({r, c}) != flashedIndexes.end()) {
        return;
    }

    flashedIndexes.insert({r, c});

    // Apply to top
    if (r > 0) {
        octopusMap[r - 1][c] += 1;
        applyFlashIfNeeded(octopusMap, r - 1, c, flashedIndexes);
    }

    // Apply to right
    if (c < MAX_OCTOPUS_MAP_COLUMNS - 1) {
        octopusMap[r][c + 1] += 1;
        applyFlashIfNeeded(octopusMap, r, c + 1, flashedIndexes);
    }

    // Apply to bottom
    if (r < MAX_OCTOPUS_MAP_ROWS - 1) {
        octopusMap[r + 1][c] += 1;
        applyFlashIfNeeded(octopusMap, r + 1, c, flashedIndexes);
    }

    // Apply to left
    if (c > 0) {
        octopusMap[r][c - 1] += 1;
        applyFlashIfNeeded(octopusMap, r, c - 1, flashedIndexes);    
    }

    // Apply to top left
    if (r > 0 && c > 0) {
        octopusMap[r - 1][c - 1] += 1;
        applyFlashIfNeeded(octopusMap, r - 1, c - 1, flashedIndexes);    
    }

    // Apply to top right
    if (r > 0 && c < MAX_OCTOPUS_MAP_COLUMNS - 1) {
        octopusMap[r - 1][c + 1] += 1;
        applyFlashIfNeeded(octopusMap, r - 1, c + 1, flashedIndexes);    
    }

    // Apply to bottom left
    if (r < MAX_OCTOPUS_MAP_ROWS - 1 && c > 0) {
        octopusMap[r + 1][c - 1] += 1;
        applyFlashIfNeeded(octopusMap, r + 1, c - 1, flashedIndexes);    
    }

    // Apply to bottom right
    if (r < MAX_OCTOPUS_MAP_ROWS - 1 && c < MAX_OCTOPUS_MAP_COLUMNS - 1) {
        octopusMap[r + 1][c + 1] += 1;
        applyFlashIfNeeded(octopusMap, r + 1, c + 1, flashedIndexes);    
    }
}

int calculateFlashes(int** octopusMap, int steps) {
    int flashes = 0;
    std::set<std::pair<int, int>> flashedIndexes;

    for (int i = 0; i < steps; ++i) {
        // Increase all energy levels by 1
        for (int r = 0; r < MAX_OCTOPUS_MAP_ROWS; ++r) {
            for(int c = 0; c < MAX_OCTOPUS_MAP_COLUMNS; ++c) {
                octopusMap[r][c] += 1;            
            }        
        }

        // Handle flashes
        for (int r = 0; r < MAX_OCTOPUS_MAP_ROWS; ++r) {
            for(int c = 0; c < MAX_OCTOPUS_MAP_COLUMNS; ++c) {
                applyFlashIfNeeded(octopusMap, r, c, flashedIndexes);
            }
        }

        // Set flashes to zero
        for(std::pair<int, int> index : flashedIndexes) {
            flashes += 1;
            octopusMap[index.first][index.second] = 0;
        }    

        flashedIndexes.clear();
    }

    return flashes;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Supply input file as first argument" << std::endl;
        return -1;    
    }

    if (argc < 3) {
        std::cerr << "Supply number of steps as second argument" << std::endl;
        return -1;    
    }

    int steps = atoi(argv[2]);

    std::ifstream inputFile;
    inputFile.open(argv[1]);

    if (inputFile.is_open()) {
        std::string inputLine;

        int** octopusMap = createArray(MAX_OCTOPUS_MAP_ROWS, MAX_OCTOPUS_MAP_COLUMNS);

        int r = 0;
        while (getline(inputFile, inputLine)) {
             for (size_t i = 0; i < inputLine.size(); ++i) {
                try {
                    char character = (inputLine[i]);
                    int number = atoi(&character);
                    octopusMap[r][i] = number;
                } catch (const std::invalid_argument& e) {
                    continue;        
                }
            }

            r++;
        }

        int flashes = calculateFlashes(octopusMap, steps);
        std::cout << flashes << std::endl;

        freeArray(octopusMap, MAX_OCTOPUS_MAP_ROWS);
    }
}
