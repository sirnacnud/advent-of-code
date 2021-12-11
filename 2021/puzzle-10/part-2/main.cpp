#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>

std::string completeLine(const std::string& line) {
    std::string added;

    for (int i = line.size() - 1; i >= 0; --i) {
        switch (line[i]) {
        case '(':
            added += ')';
            break;
        case '[':
            added += ']';
            break;
        case '{':
            added += '}';
            break;
        case '<':
            added += '>';
            break;
        }    
    }

    return added;
}

std::string completeLineIfNeeded(const std::string& line) {
    std::string parsed;

    for (size_t i = 0; i < line.size(); ++i) {
        switch (line[i]) {
        case '(': case '[': case '{': case '<':
            parsed.push_back(line[i]);
            break;
        case ')':
            if (parsed.back() == '(') {
                parsed.pop_back();            
            } else {
                return std::string();             
            }
            break;
        case ']':
            if (parsed.back() == '[') {
                parsed.pop_back();            
            } else {
                return std::string();             
            }
            break;
        case '}':
            if (parsed.back() == '{') {
                parsed.pop_back();            
            } else {
                return std::string();             
            }
            break;
        case '>':
            if (parsed.back() == '<') {
                parsed.pop_back();            
            } else {
                return std::string();            
            }
            break;
        default:
            continue;
        }
    }

    return completeLine(parsed);
}

uint64_t calculateScore(const std::string& completion) {
    uint64_t score = 0;

    for(const char& character : completion) {
        switch (character) {
        case ')':
            score *= 5;
            score += 1;
            break;
        case ']':
            score *= 5;
            score += 2;
            break;
        case '}':
            score *= 5;
            score += 3;
            break;
        case '>':
            score *= 5;
            score += 4;
            break;
        default:
            continue;        
        }    
    }

    return score;
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

        uint64_t score = 0;

        std::vector<std::string> completions;

        while (getline(inputFile, inputLine)) {
            std::string completion = completeLineIfNeeded(inputLine);

            if (!completion.empty()) {
                completions.push_back(completion);
            }
        }

        std::vector<uint64_t> scores;

        for(const std::string& completion : completions) {
            scores.push_back(calculateScore(completion));        
        }

        std::sort(scores.begin(), scores.end());

        int middleIndex = (scores.size() / 2);

        std::cout << scores[middleIndex] << std::endl;
    }
}
