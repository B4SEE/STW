#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <fstream>

/**
 * Create directories and files for the lab.
 */
void createDirectoriesAndFiles() {
    std::string keyword = "keyword";

    CreateDirectory("FILE11", NULL);
    CreateDirectory("FILE12", NULL);
    CreateDirectory("FILE13", NULL);
    CreateDirectory("FILE21", NULL);

    // Copy files (assuming files are in C:\source)
    std::vector<std::string> filesToCopy = {"file1.txt", "file2.bin", "file3.txt"};
    for (const auto& file : filesToCopy) {
        if (!CopyFile(("C:\\source\\" + file).c_str(), ("FILE11\\" + file).c_str(), FALSE)) {
            std::cerr << "Failed to copy " << file << " to FILE11" << std::endl;
            return;
        }
        if (!CopyFile(("C:\\source\\" + file).c_str(), ("FILE21\\" + file).c_str(), FALSE)) {
            std::cerr << "Failed to copy " << file << " to FILE21" << std::endl;
            return;
        }
    }

    std::ofstream outFile1("FILE11\\keyword_file.txt");
    outFile1 << keyword << " file.\n";
    outFile1.close();

    std::ofstream outFile2("FILE21\\keyword_file.bin", std::ios::binary);
    outFile2 << "Binary " << keyword << " file.\n";
    outFile2.close();
}

/**
 * Resize files to only contain the first line.
 */
void resizeFiles() {
    std::vector<std::string> files = {"FILE11\\file1.txt", "FILE11\\keyword_file.txt", "FILE21\\file1.txt", "FILE21\\keyword_file.bin"};
    for (const auto& file : files) {
        std::fstream fs(file, std::ios::in | std::ios::out | std::ios::binary);
        if (fs.is_open()) {
            fs.seekp(0, std::ios::end);
            size_t size = fs.tellp();
            fs.seekp(0, std::ios::beg);
            std::string firstLine;
            std::getline(fs, firstLine);
            fs.close();

            std::ofstream outFile(file, std::ios::binary | std::ios::trunc);
            outFile << firstLine;
            outFile.close();
        }
    }
}

/**
 * Main function.
 */
int main() {
    createDirectoriesAndFiles();

    HANDLE hReadPipe, hWritePipe;
    SECURITY_ATTRIBUTES saAttr;
    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle = TRUE;
    saAttr.lpSecurityDescriptor = NULL;

    CreatePipe(&hReadPipe, &hWritePipe, &saAttr, 0);

    resizeFiles();

    STARTUPINFO si1, si2;
    PROCESS_INFORMATION pi1, pi2;
    ZeroMemory(&si1, sizeof(si1));
    si1.cb = sizeof(si1);
    ZeroMemory(&pi1, sizeof(pi1));
    ZeroMemory(&si2, sizeof(si2));
    si2.cb = sizeof(si2);
    ZeroMemory(&pi2, sizeof(pi2));

    std::string cmdLine1 = "child1.exe " + std::to_string((intptr_t)hWritePipe);
    if (!CreateProcess(NULL, (LPSTR)cmdLine1.c_str(), NULL, NULL, TRUE, 0, NULL, NULL, &si1, &pi1)) {
        std::cerr << "CreateProcess failed for child1.exe" << std::endl;
        return 1;
    }

    std::string cmdLine2 = "child2.exe " + std::to_string((intptr_t)hReadPipe);
    if (!CreateProcess(NULL, (LPSTR)cmdLine2.c_str(), NULL, NULL, TRUE, 0, NULL, NULL, &si2, &pi2)) {
        std::cerr << "CreateProcess failed for child2.exe" << std::endl;
        return 1;
    }

    WaitForSingleObject(pi1.hProcess, INFINITE);
    WaitForSingleObject(pi2.hProcess, INFINITE);

    CloseHandle(pi1.hProcess);
    CloseHandle(pi1.hThread);
    CloseHandle(pi2.hProcess);
    CloseHandle(pi2.hThread);
    CloseHandle(hReadPipe);
    CloseHandle(hWritePipe);

    std::ifstream inFile("result.txt");
    std::string line;
    while (std::getline(inFile, line)) {
        std::cout << line << std::endl;
    }
    inFile.close();

    return 0;
}