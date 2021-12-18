#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <map>

void parseRule(const std::string& line, std::map<std::pair<char, char>, char>& rules) {
    std::stringstream ss(line);
    std::string s;

    int index = 0;
    std::pair<char, char> pair;

    while (index < 2 && getline(ss, s, '>')) {
         try {
            if (index == 0) {
                pair.first = s[0];
                pair.second = s[1];         
            } else {
                rules[pair] = s[1];
            }
        } catch (const std::invalid_argument& e) {
            continue;        
        }

        index++;
    }
}

void applyRules(std::string& pattern, const std::map<std::pair<char, char>, char>& rules, int steps) {
    for (int s = 0; s < steps; ++s) {
        for (size_t i = 0; i < pattern.size() - 1; ++i) {
            auto iter = rules.find({pattern[i], pattern[i + 1]});
            if (iter != rules.end()) {
                pattern.insert(i + 1, 1, iter->second);
                // Advance i past inserted letter
                ++i;
            }
        }
    }
}

int calculateResult(const std::string& pattern) {
    std::map<char, int> counts;
    for (const char& character : pattern) {
        auto iter = counts.find(character);

        if (iter != counts.end()) {
            counts[character] = (iter->second) + 1;
        } else {
            counts[character] = 1;        
        }    
    }

    int leastCommon = std::numeric_limits<int>::max();
    int mostCommon = 0;

    for (auto iter = counts.begin(); iter != counts.end(); ++iter) {
        if (iter->second < leastCommon) {
            leastCommon = iter->second;
        }

        if (iter->second > mostCommon) {
            mostCommon = iter->second;        
        }
    }

    return (mostCommon - leastCommon);
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
        std::string pattern;
        if (getline(inputFile, pattern)) {
            std::string inputLine;

            std::map<std::pair<char, char>, char> rules;

            while (getline(inputFile, inputLine)) {
                if (!inputLine.empty()) {
                    parseRule(inputLine, rules);
                }
            }

            applyRules(pattern, rules, steps);
            int result = calculateResult(pattern);
            
            std::cout << result << std::endl;
        }
    }
}
