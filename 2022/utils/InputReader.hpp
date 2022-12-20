#ifndef INPUT_READER_HPP
#define INPUT_READER_HPP

#include <functional>
#include <string>
#include <vector>

class InputReader {
public:
    InputReader(int argc, char* argv[]);

    int readLines(const std::function<void(const std::string&)> &function);
    int readLines(std::vector<std::string>& lines);
private:
    int mArgc;
    char** mArgv;
};

#endif
