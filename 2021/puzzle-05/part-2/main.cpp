#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct Coordinate {
    int x;
    int y;
};

struct Line {
    Coordinate start;
    Coordinate end;
};

Coordinate parseCoordinate(const std::string& string) {
    std::stringstream ss(string);
    std::string s;

    int index = 0;
    Coordinate coordinate = {};

    while (index < 2 && getline(ss, s, ',')) {
         try {
            if (index == 0) {
                coordinate.x = stoi(s);         
            } else {
                coordinate.y = stoi(s);
            }
        } catch (const std::invalid_argument& e) {
            continue;        
        }

        index++;
    }

    return coordinate;
}

Line parseLine(const std::string& string) {
    std::stringstream ss(string);
    std::string s;

    Line line = {};

    // Get start
    if (getline(ss, s, ' ')) {
        line.start = parseCoordinate(s);
    }

    // Skip -> in string
    getline(ss, s, ' ');

    // Get end
    if (getline(ss, s, ' ')) {
        line.end = parseCoordinate(s);
    }

    return line;
}

bool markPointOnCoordinateSpace(int** space, int x, int y) {
    bool isFirstIntersection = false;    

    if (space[y][x] != 0) {
        if (space[y][x] == 1) {
            isFirstIntersection = true;               
        }
        space[y][x] += 1;
    } else {
        space[y][x] = 1;
    }

    return isFirstIntersection;
}

int applyLineToCoordinateSpace(int** space, const Line& line) {
    int pointsOverlapping = 0;

    // Vertical line
    if (line.start.x == line.end.x) {
        int start = std::min(line.start.y, line.end.y);
        int end = std::max(line.start.y, line.end.y);
   
        for(int y = start; y <= end; ++y) {
            if (markPointOnCoordinateSpace(space, line.start.x, y)) {
                pointsOverlapping += 1;            
            }
        }
    // Horizontal line
    } else if (line.start.y == line.end.y) {
        int start = std::min(line.start.x, line.end.x);
        int end = std::max(line.start.x, line.end.x);
  
        for(int x = start; x <= end; ++x) {
            if (markPointOnCoordinateSpace(space, x, line.start.y)) {
                pointsOverlapping += 1;            
            }
        }
    // Diagonal
    } else {
        Coordinate start;
        Coordinate end;

        // Swap coordinates so we start from the left
        if (line.start.x > line.end.x) {
            start = line.end;
            end = line.start;        
        } else {
            start = line.start;
            end = line.end;        
        } 

        // Diagonal line is going down
        if (start.y < end.y) {
            int y = start.y;
            for(int x = start.x; x <= end.x; ++x, ++y) {
                if (markPointOnCoordinateSpace(space, x, y)) {
                    pointsOverlapping += 1;            
                }
            }
        // Going up
        } else {
            int y = start.y;
            for(int x = start.x; x <= end.x; ++x, --y) {
                if (markPointOnCoordinateSpace(space, x, y)) {
                    pointsOverlapping += 1;            
                }
            }
        }
    }

    return pointsOverlapping;
}

int** createCoordinateSpace(int rows, int columns) {   
    int** space = new int* [rows];

    for (size_t i = 0; i < rows; ++i) {
        space[i] = new int[columns];
    }

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            space[i][j] = 0;
        }
    }

    return space;
}

void freeCoordinateSpace(int** space, int rows) {
    for (size_t i = 0; i < rows; ++i) {
        delete[] space[i];    
    }

    delete[] space;
}

void printCoordinateSpace(int** space, int rows, int columns) {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            std::cout << space[i][j] << ' ';
        }
        std::cout << std::endl;
    }
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

        std::vector<Line> lines; 

        while (getline(inputFile, inputLine)) {
            Line line = parseLine(inputLine);
            lines.push_back(line);
        }

        Coordinate max = {};
        for (size_t i = 0; i < lines.size(); ++i) {
            max.x = std::max(std::max(lines[i].start.x, lines[i].end.x), max.x);
            max.y = std::max(std::max(lines[i].start.y, lines[i].end.y), max.y);
        }

        int rows = max.y + 1;
        int columns = max.x + 1;

        int** coordinateSpace = createCoordinateSpace(rows, columns);

        int overlappingPoints = 0;
        for (size_t i = 0; i < lines.size(); ++i) {
            overlappingPoints += applyLineToCoordinateSpace(coordinateSpace, lines[i]);
        }

        std::cout << overlappingPoints << std::endl;

        freeCoordinateSpace(coordinateSpace, columns);
    }
}
