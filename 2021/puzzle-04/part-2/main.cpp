#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct Board {
    int numbers[5][5];
    bool marked[5][5];
    bool alreadyWon;
};

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

void printBoard(const Board& board) {
    for (size_t i = 0; i < 5; ++i) {
        for (size_t j = 0; j < 5; ++j) {
            std::cout << board.numbers[i][j] << "\t";        
        }

        std::cout << std::endl;
    }
}

void printNumbers(const std::vector<int>& numbers) {
    for(size_t i = 0; i < numbers.size(); ++i) {
        std::cout << numbers[i];    
    }

    std::cout << std::endl;
}

bool checkColum(Board& board, int column) {
    for (size_t i = 0; i < 5; ++i) {
        if(board.marked[i][column] == false) {
            return false;        
        }    
    }

    return true;
}

bool checkRow(Board& board, int row) {
    for (size_t i = 0; i < 5; ++i) {
        if(board.marked[row][i] == false) {
            return false;        
        }    
    }

    return true;
}

int calculateUnmarkedSum(Board& board) {
    int sum = 0;

    for (size_t i = 0; i < 5; ++i) {
        for (size_t j = 0; j < 5; ++j) {
            if (!board.marked[i][j]) {
                sum += board.numbers[i][j];            
            }   
        }    
    }

    return sum;
}

bool applyCalledNumber(Board& board, int number) {
    if (board.alreadyWon) {
        return false;    
    }

    for (size_t i = 0; i < 5; ++i) {
        for (size_t j = 0; j < 5; ++j) {
            if (board.numbers[i][j] == number) {
                board.marked[i][j] = true;
                return (checkColum(board, j) || checkRow(board, i));
            }        
        }    
    }

    return false;
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

        std::vector<std::string> lines;
        while (getline(inputFile, line)) {
            lines.push_back(line);
        }

        std::vector<int> calledNumbers = parseNumbersFromLine(lines[0], ',');

        std::vector<Board> boards;

        for (size_t i = 1; i < lines.size(); i = i + 6) {
            Board board = {};
            board.alreadyWon = false;

            for (size_t j = 1; j < 6; ++j) {
                std::vector<int> numbers = parseNumbersFromLine(lines[i + j], ' ');

                for (size_t n = 0; n < numbers.size(); ++n) {
                    board.numbers[j - 1][n] = numbers[n];                
                }
            }

            //printBoard(board);
            //std::cout << std::endl;

            boards.push_back(board);
        }

        int winningBoardIndex = 0;
        int winningCalledNumber = 0;

        for (size_t i = 0; i < calledNumbers.size(); ++i) {
            for (size_t b = 0; b < boards.size(); ++b) {
                if (applyCalledNumber(boards[b], calledNumbers[i])) {
                    boards[b].alreadyWon = true;
                    winningBoardIndex = b;
                    winningCalledNumber = calledNumbers[i];
                }
            }
        }

        std::cout << "Winning board" << std::endl;
        printBoard(boards[winningBoardIndex]);
        int sum = calculateUnmarkedSum(boards[winningBoardIndex]);
        std::cout << "Score: " << sum * winningCalledNumber << std::endl;
    }
}
