#include "DirectoryHandler.h"
#include <filesystem>
#include <iostream>
#include <algorithm>
#include <cctype>

// Use the filesystem namespace for convenience
namespace fs = std::filesystem;

// Utility function to trim leading and trailing whitespace, unprintable, and non-ASCII characters
std::string DirectoryHandler::trim(const std::string& str) {
    std::string trimmed = str;

    // Remove leading whitespace, unprintable, and non-ASCII characters
    trimmed.erase(trimmed.begin(), std::find_if(trimmed.begin(), trimmed.end(), [](unsigned char ch) {
        return std::isprint(ch) && ch >= 32 && ch <= 126; // Printable ASCII range
    }));

    // Remove trailing whitespace, unprintable, and non-ASCII characters
    trimmed.erase(std::find_if(trimmed.rbegin(), trimmed.rend(), [](unsigned char ch) {
        return std::isprint(ch) && ch >= 32 && ch <= 126;
    }).base(), trimmed.end());

    return trimmed;
}

void DirectoryHandler::test()
{
    std::string path = "/home/developer";
    for (const auto & entry : fs::directory_iterator(path))
        std::cout << entry.path() << std::endl;
}

std::vector<std::string> DirectoryHandler::listDirectories(const std::string& path) {
    std::vector<std::string> directories;

    try {
        for (const auto& entry : fs::directory_iterator(path)) {
            if (entry.is_directory()) {
                std::string dirName = entry.path().filename().string();
                directories.push_back(dirName);
            }
        }
    } catch (const fs::filesystem_error& err) {
        std::cerr << "Error accessing directory: " << err.what() << std::endl;
    }

    return directories;
}
