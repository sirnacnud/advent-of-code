#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../../utils/ArrayUtils.hpp"
#include "../../utils/InputReader.hpp"
#include "../../utils/StringUtils.hpp"

#define SCREEN_HEIGHT 6
#define SCREEN_COLUMNS 40

struct CPUState {
    int cycleCount;
    int xRegister;
};

void drawPixel(int** screen, const CPUState& state) {
    int column = (state.cycleCount - 1) % SCREEN_COLUMNS;
    int row = ((state.cycleCount - 1) / SCREEN_COLUMNS);

    // Check sprite start
    if (column == state.xRegister - 1) {
        screen[row][column] = 1;
    }
    // Check sprite middle
    else if (column == state.xRegister) {
        screen[row][column] = 1;
    }
    // Check sprite end
    else if (column == state.xRegister + 1) {
        screen[row][column] = 1;    
    } else {
        screen[row][column] = 0;    
    }
}

void printScreen(int** screen) {
    for (size_t i = 0; i < SCREEN_HEIGHT; ++i) {
        for (size_t j = 0; j < SCREEN_COLUMNS; ++j) {
            if (screen[i][j] == 1) {
                std::cout << "#";
            } else {
                std::cout << ".";            
            }
        }
        std::cout << std::endl;
    }
}

int main(int argc, char* argv[]) {
    InputReader reader(argc, argv);

    CPUState state;
    state.cycleCount = 1;
    state.xRegister = 1;

    std::vector<std::string> split;
    int** screen = ArrayUtils::allocate2dIntArray(SCREEN_HEIGHT, SCREEN_COLUMNS);

    auto read = [&](const std::string& line) {
        if (line.starts_with("noop")) {
            drawPixel(screen, state);
            state.cycleCount++;
        } else {
            split.clear();
            StringUtils::split(line, split, ' ');

            try {
                int value = stoi(split[1]);

                drawPixel(screen, state);
                state.cycleCount++;

                drawPixel(screen, state);
                state.cycleCount++;

                state.xRegister += value;            
            } catch (const std::invalid_argument& e) {
            }
        }
    };

    int result = reader.readLines(read);
    
    printScreen(screen);

    ArrayUtils::free2dIntArray(screen, SCREEN_HEIGHT);

    return result;
}
