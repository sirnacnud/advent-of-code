#include "InputReader.hpp"

#include <iostream>
#include <fstream>

InputReader::InputReader(int argc, char* argv[])
    : mArgc(argc)
    , mArgv(argv)
{
}

int InputReader::readLines(const std::function<void(const std::string&)> &function) {
    if (mArgc < 2) {
        std::cerr << "Supply input file as first argument" << std::endl;
        return -1;    
    }

    std::ifstream inputFile;
    inputFile.open(mArgv[1]);

    if (inputFile.is_open()) {
        std::string inputLine;

        while (getline(inputFile, inputLine)) {
            function(inputLine);
        }
    }

    return 0;
}

int InputReader::readLines(std::vector<std::string>& lines) {
    auto readFunc = [&](const std::string& line) {
        lines.push_back(line);
    };

    return readLines(readFunc);
}

