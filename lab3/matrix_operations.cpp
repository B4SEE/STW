#include "matrix_operations.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cctype>
#include <algorithm>

/**
 * Reads data from a file and stores it in a 2D vector.
 *
 * @param filename - the name of the file to read from
 * @param rows - the number of rows in the matrix
 * @param cols - the number of columns in the matrix
 */
std::vector<std::vector<int>> readDataFromFile(const char* filename, int& rows, int& cols) {
    std::ifstream file(filename);
    std::vector<std::vector<int>> matrix;
    std::string line;
    rows = 0;
    cols = 0;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::vector<int> row;
        std::string word;
        while (iss >> word) {
            if (std::all_of(word.begin(), word.end(), ::isdigit) ||
                (word[0] == '-' && std::all_of(word.begin() + 1, word.end(), ::isdigit))) {
                row.push_back(std::stoi(word));
                }
        }
        if (!row.empty()) {
            matrix.push_back(row);
            cols = std::max(cols, static_cast<int>(row.size()));
            rows++;
        }
    }

    for (auto& row : matrix) {
        while (row.size() < cols) {
            row.push_back(0);
        }
    }

    return matrix;
}

/**
 * Processes the given matrix by removing rows that contain negative numbers.
 *
 * @param matrix - the matrix to process
 */
void processMatrix(std::vector<std::vector<int>>& matrix) {
    int rows = matrix.size();
    int cols = rows > 0 ? matrix[0].size() : 0;

    for (int i = 0; i < rows; ++i) {
        bool hasNegative = false;
        for (int j = 0; j < cols; ++j) {
            if (matrix[i][j] < 0) {
                hasNegative = true;
                break;
            }
        }
        if (hasNegative) {
            std::fill(matrix[i].begin(), matrix[i].end(), 0);
            matrix.push_back(matrix[i]);
            matrix.erase(matrix.begin() + i);
            --i;
            --rows;
        }
    }
}