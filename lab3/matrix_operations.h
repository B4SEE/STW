#pragma once

#ifdef MATRIXOPERATIONS_EXPORTS
#define MATRIXOPERATIONS_API __declspec(dllexport)
#else
#define MATRIXOPERATIONS_API __declspec(dllimport)
#endif

#include <vector>

extern "C" {
    MATRIXOPERATIONS_API std::vector<std::vector<int>> readDataFromFile(const char* filename, int& rows, int& cols);
    MATRIXOPERATIONS_API void processMatrix(std::vector<std::vector<int>>& matrix);
}