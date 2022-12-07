#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

enum Play {
    rock,
    paper,
    scissor
};

std::pair<Play, Play> parseRoundFromLine(const std::string& line) {
    std::stringstream ss(line);
    std::string s;

    std::pair<Play, Play> round;
    while (getline(ss, s, ' ')) {
        if (s == "A") {
            round.first = rock;
        } else if (s == "B") {
            round.first = paper;            
        } else if (s == "C") {
            round.first = scissor;            
        } else if (s == "X") {
            round.second = rock;            
        } else if (s == "Y") {
            round.second = paper;
        } else if (s == "Z") {
            round.second = scissor;            
        }
    }

    return round;
}

int calculateScore(std::pair<Play, Play> round) {
    int score = 0;

    // Check for tie
    if (round.first == round.second) {
        score += 3;
    } else {
        // Rock beats scissor
        if (round.second == rock && round.first == scissor) {
            score += 6;
        // Paper beats rock
        } else if (round.second == paper && round.first == rock) {
            score += 6;
        // Scissor beats paper      
        } else if (round.second == scissor && round.first == paper) {
            score += 6;
        }        
    }

    // Add score for selected shape
    switch (round.second) {
    case rock:
        score += 1;
        break;
    case paper:
        score += 2;
        break;
    case scissor:
        score += 3;
        break;    
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

        std::vector<std::pair<Play, Play>> rounds;
        int score = 0;

        while (getline(inputFile, inputLine)) {
            std::pair<Play, Play> round = parseRoundFromLine(inputLine);
            int roundScore = calculateScore(round);
            score += roundScore;
        }

        std::cout << score << std::endl;
    }
}
