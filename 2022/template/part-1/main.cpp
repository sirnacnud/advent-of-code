#include <iostream>
#include <fstream>
#include <string>

#include "../../utils/InputReader.hpp"

int main(int argc, char* argv[]) {
    InputReader reader(argc, argv);

    auto read = [](const std::string& line) {
    };

    int result = reader.readLines(read);

    return result;
}
