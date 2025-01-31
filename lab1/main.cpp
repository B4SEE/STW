#include <windows.h>
#include <iostream>
#include <string>

/**
 * Create directories
 */
void CreateDirectories() {
    // Create directories
    CreateDirectory("FILE11", NULL);
    CreateDirectory("FILE11/FILE12", NULL);
    CreateDirectory("FILE21", NULL);
    CreateDirectory("FILE21/FILE22", NULL);

    std::cout << "Directories created successfully." << std::endl;
}

/**
 * Traverse directories
 *
 * @param path - directory path
 */
void TraverseDirectory(const std::string& path) {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile((path + "\\*").c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        std::cerr << "Error opening directory: " << path << std::endl;
        return;
    }

    do {
        if (strcmp(findFileData.cFileName, ".") != 0 && strcmp(findFileData.cFileName, "..") != 0) {
            std::cout << "Found: " << findFileData.cFileName << std::endl;
            if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                TraverseDirectory(path + "\\" + findFileData.cFileName);
            }
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
}

/**
 * Create file in directory (FILE21/FILE22, example.txt)
 *
 * @param path - directory path
 * @param fileName - file name
 */
void CreateFileInDirectory(std::string path = "FILE21\\FILE22", std::string fileName = "example.txt") {
    HANDLE hFile = CreateFile((path + "\\" + fileName).c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        std::cerr << "Error creating file." << std::endl;
        return;
    }
    CloseHandle(hFile);
    std::cout << "File created successfully." << std::endl;
}

/**
 * Set file attributes and time (hidden, creation time)
 *
 * @param path - directory path
 * @param fileName - file name
 */
void SetFileAttributesAndTime(std::string path = "FILE21\\FILE22", std::string fileName = "example.txt") {
    // Set file as hidden
    if (!SetFileAttributes((path + "\\" + fileName).c_str(), FILE_ATTRIBUTE_HIDDEN)) {
        std::cerr << "Error setting file attributes." << std::endl;
        return;
    }

    // Modify creation time
    HANDLE hFile = CreateFile("FILE21\\FILE22\\example.txt", FILE_WRITE_ATTRIBUTES, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        std::cerr << "Error opening file." << std::endl;
        return;
    }

    FILETIME ft;
    SYSTEMTIME st;
    GetSystemTime(&st);
    SystemTimeToFileTime(&st, &ft);
    if (!SetFileTime(hFile, &ft, NULL, NULL)) {
        std::cerr << "Error setting file time." << std::endl;
    }

    CloseHandle(hFile);
    std::cout << "File attributes and time set successfully." << std::endl;
}

/**
 * Copy files from one directory to another
 *
 * @param sourceDir - source directory
 * @param destDir - destination directory
 */
void CopyFiles(const std::string& sourceDir, const std::string& destDir) {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile((sourceDir + "\\*").c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        std::cerr << "Error opening directory: " << sourceDir << std::endl;
        return;
    }

    do {
        if (strcmp(findFileData.cFileName, ".") != 0 && strcmp(findFileData.cFileName, "..") != 0) {
            std::string sourceFile = sourceDir + "\\" + findFileData.cFileName;
            std::string destFile = destDir + "\\" + findFileData.cFileName;
            if (!CopyFile(sourceFile.c_str(), destFile.c_str(), FALSE)) {
                std::cerr << "Error copying file: " << findFileData.cFileName << std::endl;
            }
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
    std::cout << "Files copied successfully." << std::endl;
}

/**
 * Find files by extension
 *
 * @param path - directory path
 * @param extension - file extension
 */
void FindFilesByExtension(const std::string& path, const std::string& extension) {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile((path + "\\*." + extension).c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        std::cerr << "Error finding files." << std::endl;
        return;
    }

    do {
        std::cout << "Found: " << findFileData.cFileName << std::endl;
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
}

/**
 * Append data to file
 *
 * @param filePath - file path
 * @param data - data to append
 */
void AppendToFile(const std::string& filePath, const std::string& data) {
    HANDLE hFile = CreateFile(filePath.c_str(), FILE_APPEND_DATA, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        std::cerr << "Error opening file." << std::endl;
        return;
    }

    DWORD fileSize = GetFileSize(hFile, NULL);
    std::cout << "File size: " << fileSize << " bytes" << std::endl;

    DWORD bytesWritten;
    WriteFile(hFile, data.c_str(), data.size(), &bytesWritten, NULL);
    CloseHandle(hFile);
    std::cout << "Data appended successfully." << std::endl;
}

/**
 * Find hidden files starting with 'a'
 *
 * @param path - directory path
 */
void FindHiddenFilesStartingWithA(const std::string& path) {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile((path + "\\a*").c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        std::cerr << "Error finding files." << std::endl;
        return;
    }

    do {
        if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) {
            std::cout << "Found hidden file: " << findFileData.cFileName << std::endl;
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
}

/**
 * Lock last 1 KB of file
 *
 * @param filePath - file path
 */
void LockLastKB(const std::string& filePath) {
    HANDLE hFile = CreateFile(filePath.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        std::cerr << "Error opening file." << std::endl;
        return;
    }

    DWORD fileSize = GetFileSize(hFile, NULL);
    DWORD lockOffset = fileSize - 1024; // Last 1 KB
    if (!LockFile(hFile, lockOffset, 0, 1024, 0)) {
        std::cerr << "Error locking file." << std::endl;
    } else {
        std::cout << "File locked successfully." << std::endl;
    }

    CloseHandle(hFile);
}

/**
 * Main function
 */
int main() {
    // Select the operation to perform
    CreateDirectories();
    TraverseDirectory("FILE21");
    CreateFileInDirectory();
    SetFileAttributesAndTime();
    CopyFiles("FILE21\\FILE22", "FILE11\\FILE12");
    FindFilesByExtension("FILE21\\FILE22", "txt");
    AppendToFile("FILE21\\FILE22\\example.txt", "DATA");
    AppendToFile("FILE21\\FILE22\\example.txt", "Variant No 2");

    // Create hidden file starting with 'a' for testing
    CreateFileInDirectory("FILE21\\FILE22", "a_example.txt");
    SetFileAttributesAndTime("FILE21\\FILE22", "a_example.txt");

    FindHiddenFilesStartingWithA("FILE21\\FILE22");
    LockLastKB("FILE21\\FILE22\\example.txt");
    return 0;
}
