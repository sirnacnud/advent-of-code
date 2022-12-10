#ifndef STRING_UTILS_HPP
#define STRING_UTILS_HPP

#include <string>
#include <vector>

namespace StringUtils {
    void split(const std::string& input, std::vector<std::string>& output, char separator);
};

#endif
