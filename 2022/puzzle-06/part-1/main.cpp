#include <iostream>
#include <fstream>
#include <set>
#include <string>

int findEndOfMarker(const std::string& line) {
    int start = 0;
    int end = start + 3;
    bool found = false;

    std::set<char> characters;

    while (!found) {
        for (int i = start; i <= end; ++i) {
            characters.insert(line[i]);      
        }

        if (characters.size() == 4) {
            found = true;        
        } else {
            characters.clear();
            start += 1;
            end += 1;
        }
    }

    return end;    
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

        while (getline(inputFile, inputLine)) {
            int count = findEndOfMarker(inputLine);
            std::cout << count + 1 << std::endl;
        }
    }
}
