#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../../utils/InputReader.hpp"

int main(int argc, char* argv[]) {
    InputReader reader(argc, argv);

    std::vector<std::string> lines;
    int result = reader.readLines(lines);

    if (result == 0) {
    
    }

    return result;
}
