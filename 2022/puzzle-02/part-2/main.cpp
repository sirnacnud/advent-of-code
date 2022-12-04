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

enum Outcome {
    win,
    lose,
    tie
};

std::pair<Play, Outcome> parseRoundFromLine(const std::string& line) {
    std::stringstream ss(line);
    std::string s;

    std::pair<Play, Outcome> round;
    while (getline(ss, s, ' ')) {
        try {
            if (s == "A") {
                round.first = rock;
            } else if (s == "B") {
                round.first = paper;            
            } else if (s == "C") {
                round.first = scissor;            
            } else if (s == "X") {
                round.second = lose;            
            } else if (s == "Y") {
                round.second = tie;
            } else if (s == "Z") {
                round.second = win;            
            }
        } catch (const std::invalid_argument& e) {
            continue;        
        }
    }

    return round;
}

int calculateScore(std::pair<Play, Outcome> round) {
    int score = 0;

    Play shape;

    // Check for tie
    if (round.second == tie) {
        score += 3;
        shape = round.first;
    } else {
        if (round.second == win) {
            score += 6;

            // Paper beats rock
            if (round.first == rock) {
                shape = paper;
            // Scissor beats paper
            } else if (round.first == paper) {
                shape = scissor;
            // Rock beats scissor   
            } else if (round.first == scissor) {
                shape = rock;            
            }
        } else if (round.second == lose) {
            // Rock beats scissor
            if (round.first == rock) {
                shape = scissor;
            // Paper beats rock
            } else if (round.first == paper) {
                shape = rock;
            // Scissor beats paper    
            } else if (round.first == scissor) {
                shape = paper;            
            }
        }       
    }

    // Add score for selected shape
    switch (shape) {
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

        std::vector<std::pair<Play, Outcome>> rounds;
        int score = 0;

        while (getline(inputFile, inputLine)) {
            std::pair<Play, Outcome> round = parseRoundFromLine(inputLine);
            int roundScore = calculateScore(round);
            score += roundScore;
        }

        std::cout << score << std::endl;
    }
}
