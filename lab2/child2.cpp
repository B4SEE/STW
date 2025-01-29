#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <fstream>

/**
 * Child2 process that reads the shortest file in FILE11 and FILE21 directories
 *
 * @param hReadPipe - handle to the read end of the pipe
 */
void child2Process(HANDLE hReadPipe) {
    char buffer[256];
    DWORD bytesRead;
    ReadFile(hReadPipe, buffer, sizeof(buffer), &bytesRead, NULL);
    std::string shortestFile(buffer);

    std::string directory = "FILE21";
    std::vector<std::string> files = {"file1.txt", "file2.bin", "file3.txt", "keyword_file.bin"};
    std::string shortestFile2;
    size_t shortestSize2 = SIZE_MAX;

    for (const auto& file : files) {
        std::ifstream inFile(directory + "\\" + file, std::ios::binary | std::ios::ate);
        size_t fileSize = inFile.tellg();
        inFile.close();

        if (fileSize < shortestSize2) {
            shortestSize2 = fileSize;
            shortestFile2 = file;
        }
    }

    std::ofstream outFile("result.txt");
    outFile << "Shortest file in FILE11: " << shortestFile << std::endl;
    outFile << "Shortest file in FILE21: " << shortestFile2 << std::endl;
    outFile.close();

    CloseHandle(hReadPipe);
}

/**
 * Main entry point for the child2 process
 *
 * @param argc - number of command line arguments
 * @param argv - array of command line arguments
 */
int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: child2.exe <hReadPipe>" << std::endl;
        return 1;
    }

    HANDLE hReadPipe = (HANDLE)(intptr_t)std::stoll(argv[1]);
    child2Process(hReadPipe);

    return 0;
}