#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <fstream>

/**
 * Child1 process that reads the files in the FILE11 directory and sends the name of the file with the smallest size to the parent process.
 *
 * @param hWritePipe - the write pipe to send the name of the file with the smallest size to the parent process
 */
void child1Process(HANDLE hWritePipe) {
    std::string directory = "FILE11";
    std::vector<std::string> files = {"file1.txt", "file2.bin", "file3.txt", "keyword_file.txt"};
    std::string shortestFile;
    size_t shortestSize = SIZE_MAX;

    for (const auto& file : files) {
        std::ifstream inFile(directory + "\\" + file, std::ios::binary | std::ios::ate);
        size_t fileSize = inFile.tellg();
        inFile.close();

        if (fileSize < shortestSize) {
            shortestSize = fileSize;
            shortestFile = file;
        }
    }

    DWORD bytesWritten;
    WriteFile(hWritePipe, shortestFile.c_str(), shortestFile.size() + 1, &bytesWritten, NULL);

    CloseHandle(hWritePipe);
}

/**
 * Main entry point for the child1 process.
 *
 * @param argc - the number of command-line arguments
 * @param argv - the command-line arguments
 */
int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: child1.exe <hWritePipe>" << std::endl;
        return 1;
    }

    HANDLE hWritePipe = (HANDLE)(intptr_t)std::stoll(argv[1]);
    child1Process(hWritePipe);

    return 0;
}