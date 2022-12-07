#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

std::pair<std::string, std::string> splitAssignments(const std::string& line) {
    std::stringstream ss(line);
    std::string s;

    int count = 0;
    std::pair<std::string, std::string> split;
    while (getline(ss, s, ',')) {
        if (count == 0) {
            split.first = s;        
        } else {
            split.second = s;            
        }

        count++;
    }

    return split;
}

std::pair<int, int> splitIdentifiers(const std::string& line) {
    std::stringstream ss(line);
    std::string s;

    int count = 0;
    std::pair<int, int> split;
    while (getline(ss, s, '-')) {
        try {
            if (count == 0) {
                split.first = stoi(s);        
            } else {
                split.second = stoi(s);            
            }
        } catch (const std::invalid_argument& e) {
            continue;        
        }

        count++;
    }

    return split;
}

bool checkForOverlap(std::pair<int, int> assignmentOne, std::pair<int, int> assignmentTwo) {
    // Check if one is fully before two
    if (assignmentOne.second < assignmentTwo.first) {
        return false;
    }

    // Check if one is fully after two
    if (assignmentOne.first > assignmentTwo.second) {
        return false;
    }

    return true;
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

        int overlappingCount = 0;

        while (getline(inputFile, inputLine)) {
            std::pair<std::string, std::string> assignments = splitAssignments(inputLine);
            std::pair<int, int> firstAssignment = splitIdentifiers(assignments.first);
            std::pair<int, int> secondAssignment = splitIdentifiers(assignments.second);

            if (checkForOverlap(firstAssignment, secondAssignment)) {
                overlappingCount++;           
            }
        }

        std::cout << overlappingCount << std::endl;
    }
}
