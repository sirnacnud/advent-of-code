#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

std::vector<int> parseNumbersFromLine(const std::string& line, char separator) {
    std::stringstream ss(line);
    std::string s;

    std::vector<int> numbers;
    while (getline(ss, s, separator)) {
        try {
            int number = stoi(s);
            numbers.push_back(number);
        } catch (const std::invalid_argument& e) {
            continue;        
        }
    }

    return numbers;
}

bool hasPrefix(const std::string& string, const std::string& prefix) {
    auto result = std::mismatch(prefix.begin(), prefix.end(), string.begin());
    return (result.first == prefix.end());
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

        int depth = 0;
        int position = 0;
        int aim = 0;

        while (getline(inputFile, line)) {
            if (hasPrefix(line, "forward")) {
                int value = parseNumbersFromLine(line, ' ')[0];
                position += value;
                depth += (aim * value);
            } else if (hasPrefix(line, "up")) {
                int value = parseNumbersFromLine(line, ' ')[0];
                aim -= value;
            } else if (hasPrefix(line, "down")) {
                int value = parseNumbersFromLine(line, ' ')[0];
                aim += value;
            }
        }

        std::cout << "depth " << depth << std::endl;
        std::cout << "position " << position << std::endl;
        std::cout << depth * position << std::endl;
    }
}

