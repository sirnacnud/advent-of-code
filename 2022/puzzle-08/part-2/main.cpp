#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../../utils/InputReader.hpp"

int findScenicScore(const std::vector<std::string>& grid, int x, int y) {
    char height = grid[y][x];

    // Check top
    int topDistance = 0;
    for (int row = y - 1; row >= 0; --row) {
        topDistance++;
        if (grid[row][x] >= height) {
            break;
        }
    }

    // Check botton
    int bottomDistance = 0;
    for (int row = y + 1; row < grid.size(); ++row) {
        bottomDistance++;
        if (grid[row][x] >= height) {
            break;
        }
    }

    // Check right
    int rightDistance = 0;
    for (int col = x + 1; col < grid[y].size(); ++col) {
        rightDistance++;
        if (grid[y][col] >= height) {
            break;
        }
    }

     // Check left
    int leftDistance = 0;
    for (int col = x - 1; col >= 0; --col) {
        leftDistance++;
        if (grid[y][col] >= height) {
            break;
        }
    }

    return (topDistance * bottomDistance * rightDistance * leftDistance);
}

int main(int argc, char* argv[]) {
    InputReader reader(argc, argv);

    std::vector<std::string> lines;
    int result = reader.readLines(lines);

    if (result == 0) {
        int columnCount = lines[0].size();
        int maxScore = 0;

        for (int j = 1; j <= lines.size() - 2; ++j) {
            for (int i = 1; i <= columnCount - 2; ++i) {
                int score = findScenicScore(lines, j, i);
                if (score > maxScore) {
                    maxScore = score;
                }
            }
        }

        std::cout << maxScore << std::endl;
    }

    return result;
}
