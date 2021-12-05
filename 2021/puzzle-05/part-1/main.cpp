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

void removeDiagonalLines(std::vector<Line>& lines) {
    std::erase_if(lines, [](Line line) {
        return (line.start.x != line.end.x && line.start.y != line.end.y);
    });
}

void orientLines(std::vector<Line>& lines) {
    for (size_t i = 0; i < lines.size(); ++i) {
        Line& line = lines[i];

        // Swap coordinates so they go from 0,0 to x,y
        if (line.start.x > line.end.x || line.start.y > line.end.y) {
            Coordinate start = line.start;
            line.start = line.end;
            line.end = start;     
        }
    }
}

int applyLineToCoordinateSpace(int** space, const Line& line) {
    int pointsOverlapping = 0;

    // Vertical line
    if (line.start.x == line.end.x) {
        //std::cout << "Vertical: " << line.start.x << ',' << line.start.y << " -> " << line.end.x << "," << line.end.y << std::endl;   
        for(size_t i = line.start.y; i <= line.end.y; ++i) {
            if (space[i][line.start.x] != 0) {
                if (space[i][line.start.x] == 1) {
                    pointsOverlapping += 1;                
                }
                space[i][line.start.x] += 1;
            } else {
                space[i][line.start.x] = 1;
            }
        }
    } else {
        //std::cout << "Horizontal: " << line.start.x << ',' << line.start.y << " -> " << line.end.x << "," << line.end.y << std::endl;  
        for(size_t i = line.start.x; i <= line.end.x; ++i) {
            if (space[line.start.y][i] != 0) {
                if (space[line.start.y][i] == 1) {
                    pointsOverlapping += 1;
                }
                space[line.start.y][i] += 1;
            } else {
                space[line.start.y][i] = 1;
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

        removeDiagonalLines(lines);
        orientLines(lines);

        /*for (size_t i = 0; i < lines.size(); ++i) {
            std::cout << lines[i].start.x << ',' << lines[i].start.y << " -> " << lines[i].end.x << "," << lines[i].end.y << std::endl;        
        }*/

        Coordinate max = {};
        for (size_t i = 0; i < lines.size(); ++i) {
            max.x = std::max(lines[i].end.x, max.x);
            max.y = std::max(lines[i].end.y, max.y);
        }

        std::cout << max.x << "," << max.y << std::endl;

        int rows = max.y + 1;
        int columns = max.x + 1;

        std::cout << rows << " x " << columns << std::endl;

        int** coordinateSpace = createCoordinateSpace(rows, columns);

        int overlappingPoints = 0;

        //printCoordinateSpace(coordinateSpace, rows, columns);

        for (size_t i = 0; i < lines.size(); ++i) {
            overlappingPoints += applyLineToCoordinateSpace(coordinateSpace, lines[i]);
        }

        //printCoordinateSpace(coordinateSpace, rows, columns);

        freeCoordinateSpace(coordinateSpace, columns);

        std::cout << overlappingPoints << std::endl;
    }
}
