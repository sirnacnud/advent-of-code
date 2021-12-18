#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <map>
#include <vector>

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

void addToPairCounts(std::map<std::pair<char, char>, uint64_t>& pairCounts, const std::pair<char, char>& pair, uint64_t count) {
    auto iter = pairCounts.find(pair);
    if (iter != pairCounts.end()) {
        pairCounts[pair] = iter->second + count;
    } else {
        pairCounts[pair] = count;                
    }
}

void addCharacterToCounts(std::map<char, uint64_t>& counts, char character, uint64_t count) {
     auto countsIter = counts.find(character);

    if (countsIter != counts.end()) {
        counts[character] = (countsIter->second) + count;
    } else {
        counts[character] = count;        
    }   
}

void applyRules(std::map<std::pair<char, char>, uint64_t>& pairCounts, const std::map<std::pair<char, char>, char>& rules, std::map<char, uint64_t>& counts, int steps) {
     std::map<std::pair<char, char>, uint64_t> newPairs;
    
    for (int s = 0; s < steps; ++s) {
        for (auto pairIter = pairCounts.begin(); pairIter != pairCounts.end();) {
            auto ruleIter = rules.find(pairIter->first);
            if (ruleIter != rules.end()) {
                addCharacterToCounts(counts, ruleIter->second, pairIter->second);
                addToPairCounts(newPairs, {pairIter->first.first, ruleIter->second}, pairIter->second);
                addToPairCounts(newPairs, {ruleIter->second, pairIter->first.second}, pairIter->second);
                pairIter = pairCounts.erase(pairIter);
            } else {
                ++pairIter;            
            }
        }

        for (auto pair : newPairs) {
            addToPairCounts(pairCounts, pair.first, pair.second);        
        }
        newPairs.clear();
    }
}

uint64_t calculateResult(std::map<char, uint64_t>& counts) {
    uint64_t leastCommon = std::numeric_limits<uint64_t>::max();
    uint64_t mostCommon = 0;

    for (auto iter = counts.begin(); iter != counts.end(); ++iter) {
        std::cout << iter->first << " " << iter->second << std::endl;
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

            std::map<char, uint64_t> counts;

            for (size_t i = 0; i < pattern.size(); ++i) {
                addCharacterToCounts(counts, pattern[i], 1);
            }

            std::map<std::pair<char, char>, uint64_t> pairCounts;
            for (size_t i = 0; i < pattern.size() - 1; ++i) {
                std::pair<char, char> pair = {pattern[i], pattern[i + 1]};
                addToPairCounts(pairCounts, pair, 1);
            }

            applyRules(pairCounts, rules, counts, steps);

            uint64_t result = calculateResult(counts);
            
            std::cout << result << std::endl;
        }
    }
}
