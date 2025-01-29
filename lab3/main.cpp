#include <iostream>
#include <fstream>
#include "matrix_operations.h"

/**
 * Generates a file with the given filename and writes test data to it.
 *
 * @param filename - the name of the file to write to
 */
void generateFile(const char* filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "1 2 3\n";
        file << "4 5 6\n";
        file << "-7 8 9\n";
        file << "10 11 12\n";
        file << "text data\n";
        file << "13 14 text 15\n";
        file.close();
    } else {
        std::cerr << "Unable to open file for writing" << std::endl;
    }
}

int main() {
    const char* filename = "data.txt";
    generateFile(filename);

    int rows, cols;
    std::vector<std::vector<int>> matrix = readDataFromFile(filename, rows, cols);

    std::cout << "Original Matrix:" << std::endl;
    for (const auto& row : matrix) {
        for (int num : row) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

    processMatrix(matrix);

    std::cout << "Processed Matrix:" << std::endl;
    for (const auto& row : matrix) {
        for (int num : row) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}