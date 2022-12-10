#include "StringUtils.hpp"

#include <sstream>

void StringUtils::split(const std::string& input, std::vector<std::string>& output, char separator) {
    std::stringstream ss(input);
    std::string s;

    while (getline(ss, s, separator)) {
        output.push_back(s);
    }
}
