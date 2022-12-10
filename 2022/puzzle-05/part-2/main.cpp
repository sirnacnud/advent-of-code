#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <vector>

#include "../../utils/StringUtils.hpp"

struct MoveOperation {
    int count;
    int origin;
    int destination;
};

void parseMoveOperation(MoveOperation& operation, const std::string& line) {
    std::vector<std::string> split;
    StringUtils::split(line, split, ' ');

    try {
        operation.count = stoi(split[1]);
        operation.origin = stoi(split[3]);
        operation.destination = stoi(split[5]);    
    } catch (const std::invalid_argument& e) {
    }
}

void parseRow(std::vector<std::list<char>>& stacks, const std::string& row) {
    for (size_t i = 1; i < row.size(); i += 4) {
        if (row[i] != ' ') {
            int stacksIndex = (i - 1) / 4;
            stacks[stacksIndex].push_back(row[i]);
        }
    }
}

void printStack(const std::list<char>& stack) {
    for (auto iter = stack.begin(); iter != stack.end(); ++iter) {
        std::cout << *iter;    
    }
}

void printStacks(const std::vector<std::list<char>>& stacks) {
    for (auto iter = stacks.begin(); iter != stacks.end(); ++iter) {
        printStack(*iter);
        std::cout << std::endl;        
    }
}

void applyMove(std::vector<std::list<char>>& stacks, const MoveOperation& move) {
    std::vector<char> tempStack;    

    for(int i = 0; i < move.count; ++i) {
        char supply = stacks[move.origin - 1].front();
        stacks[move.origin - 1].pop_front();
        tempStack.push_back(supply);  
    }

    while (!tempStack.empty()) {
        char supply = tempStack.back();
        tempStack.pop_back();
        stacks[move.destination - 1].push_front(supply);
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

        std::vector<std::string> rows;
        std::vector<MoveOperation> moves;
        int stackCount = 0;

        while (getline(inputFile, inputLine)) {
            size_t index = inputLine.find("[");
            // Found stack row
            if (index != std::string::npos) {
                rows.push_back(inputLine);
            // Stack numbering
            } else if (inputLine[0] == ' ') {
                size_t size = inputLine.size();
                char character = inputLine[size - 2];
                stackCount = atoi(&character);
            } else if (inputLine == "") {
                continue;
            // Move instructions
            } else {
                MoveOperation move;
                parseMoveOperation(move, inputLine);
                moves.push_back(move);
            }
        }

        std::vector<std::list<char>> stacks(stackCount);
        for (auto iter = rows.begin(); iter != rows.end(); ++iter) {
            parseRow(stacks, *iter);
        }

        for (auto iter = moves.begin(); iter != moves.end(); ++iter) {
            applyMove(stacks, *iter);        
        }

        std::string topCrates;
        for (auto iter = stacks.begin(); iter != stacks.end(); ++iter) {
            topCrates.push_back(iter->front());        
        }

        std::cout << topCrates << std::endl;
    }
}
