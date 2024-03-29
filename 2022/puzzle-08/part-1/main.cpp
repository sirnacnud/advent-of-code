#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../../utils/InputReader.hpp"

bool checkIfVisibleFromOutside(const std::vector<std::string>& grid, int x, int y) {
    char height = grid[y][x];

    // Check top
    bool topBlocked = false;
    for (int row = y - 1; row >= 0; --row) {
        if (grid[row][x] >= height) {
            topBlocked = true;
            break;
        }
    }

    if (!topBlocked) {
        return true;
    }

    // Check botton
    bool bottomBlocked = false;
    for (int row = y + 1; row < grid.size(); ++row) {
        if (grid[row][x] >= height) {
            bottomBlocked = true;
            break;
        }
    }

    if (!bottomBlocked) {
        return true;
    }

    // Check right
    bool rightBlocked = false;
    for (int col = x + 1; col < grid[y].size(); ++col) {
        if (grid[y][col] >= height) {
            rightBlocked = true;
            break;
        }
    }

    if (!rightBlocked) {
        return true;
    }

     // Check left
    bool leftBlocked = false;
    for (int col = x - 1; col >= 0; --col) {
        if (grid[y][col] >= height) {
            leftBlocked = true;
            break;
        }
    }

    if (!leftBlocked) {
        return true;
    }

    return false;
}

int main(int argc, char* argv[]) {
    InputReader reader(argc, argv);

    std::vector<std::string> lines;
    int result = reader.readLines(lines);

    if (result == 0) {
        int columnCount = lines[0].size();
        int rowCount = lines.size();
        int visibleCount = (columnCount * 2) + ((rowCount - 2) * 2);

        for (int j = 1; j <= lines.size() - 2; ++j) {
            for (int i = 1; i <= columnCount - 2; ++i) {
                if (checkIfVisibleFromOutside(lines, j, i)) {
                    visibleCount++;
                }
            }
        }

        std::cout << visibleCount << std::endl;
    }

    return result;
}
