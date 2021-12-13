#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <vector>

enum FoldAxis {
    X,
    Y
};

struct Fold {
    int value;
    FoldAxis axis;
};

Fold parseFold(const std::string& line) {
    std::stringstream ss(line);
    std::string s;    
    
    bool isY = false;
    bool isX = false;

    if(getline(ss, s, '=')) {
        switch (s.back()) {
        case 'y':
            isY = true;
            break;
        case 'x':
            isX = true;
            break;         
        }
    }

    Fold fold = {};

    if (getline(ss, s, '=')) {
        try {
            if (isY == true) {
                fold.axis = Y;
                fold.value = stoi(s);         
            } else if (isX == true) {
                fold.axis = X;
                fold.value = stoi(s);
            }
        } catch (const std::invalid_argument& e) {}   
    }

    return fold;
}

std::pair<int, int> parseCoordinate(const std::string& line) {
    std::stringstream ss(line);
    std::string s;

    int index = 0;
    int x = 0;
    int y = 0;

    while (index < 2 && getline(ss, s, ',')) {
         try {
            if (index == 0) {
                x = stoi(s);         
            } else {
                y = stoi(s);
            }
        } catch (const std::invalid_argument& e) {
            continue;        
        }

        index++;
    }

    return {x, y};
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

        std::set<std::pair<int, int>> dots;
        std::vector<Fold> folds;

        while (getline(inputFile, inputLine)) {
            if (inputLine.starts_with("fold along")) {
                folds.push_back(parseFold(inputLine));
            } else if (!inputLine.empty()) {
                std::pair<int, int> coordinate = parseCoordinate(inputLine);
                dots.insert(coordinate);
            }
        }

        std::vector<std::pair<int, int>> foldedCoordinates;

        const Fold& fold = folds[0];
        for (std::set<std::pair<int, int>>::iterator iter = dots.begin(); iter != dots.end();) {
            std::pair<int, int> coordinate = *iter;

            if (fold.axis == Y) {
                if (coordinate.second > fold.value) {
                    int amountOver = (coordinate.second - fold.value);
                    int newY = (fold.value - amountOver);
                    foldedCoordinates.push_back({coordinate.first, newY});
                    iter = dots.erase(iter);
                } else {
                    ++iter;
                }
            } else if (fold.axis == X) {
                if (coordinate.first > fold.value) {
                    int amountOver = (coordinate.first - fold.value);
                    int newX = (fold.value - amountOver);
                    foldedCoordinates.push_back({newX, coordinate.second});
                    iter = dots.erase(iter);
                } else {
                    ++iter;                
                }
            }
        }

        for (std::pair<int, int> coordinate : foldedCoordinates) {
            dots.insert(coordinate);        
        }

        std::cout << dots.size() << std::endl;
    }
}
