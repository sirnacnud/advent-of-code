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

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Supply input file as first argument" << std::endl;
        return -1;    
    }

    std::ifstream inputFile;
    inputFile.open(argv[1]);

    if (inputFile.is_open()) {
        std::string inputLine;

        int fullyContained = 0;

        while (getline(inputFile, inputLine)) {
            std::pair<std::string, std::string> assignments = splitAssignments(inputLine);
            std::pair<int, int> firstAssignment = splitIdentifiers(assignments.first);
            std::pair<int, int> secondAssignment = splitIdentifiers(assignments.second);

            // Check shortest length
            int lengthOne = firstAssignment.second - firstAssignment.first;
            int lengthTwo = secondAssignment.second - secondAssignment.first;

            if (lengthOne < lengthTwo) {
                if (firstAssignment.first >= secondAssignment.first && firstAssignment.first <= secondAssignment.second && firstAssignment.second <= secondAssignment.second) {
                    fullyContained++;                
                }
            } else if (lengthTwo < lengthOne){
                if (secondAssignment.first >= firstAssignment.first && secondAssignment.first <= firstAssignment.second && secondAssignment.second <= firstAssignment.second) {
                    fullyContained++;                
                }
            } else {
                // If same length, then check for same ranges
                if (firstAssignment.first == secondAssignment.first && firstAssignment.second == secondAssignment.second) {
                    fullyContained++;           
                }
            }
        }

        std::cout << fullyContained << std::endl;
    }
}
