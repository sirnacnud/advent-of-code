#include "ArrayUtils.hpp"

#include <iostream>

int** ArrayUtils::allocate2dIntArray(int rows, int columns) {
    int** array = new int* [rows];

    for (size_t i = 0; i < rows; ++i) {
        array[i] = new int[columns];
    }

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            array[i][j] = 0;
        }
    }

    return array;
}

void print2dIntArray(int** array, int rows, int columns) {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            std::cout << array[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

void ArrayUtils::free2dIntArray(int** array, int rows) {
    for (size_t i = 0; i < rows; ++i) {
        delete[] array[i];    
    }

    delete[] array;
};
