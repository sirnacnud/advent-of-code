#ifndef ARRAY_UTILS_HPP
#define ARRAY_UTILS_HPP

namespace ArrayUtils {
    int** allocate2dIntArray(int rows, int columns);

    void print2dIntArray(int** array, int rows, int columns);

    void free2dIntArray(int** array, int rows);
};

#endif
