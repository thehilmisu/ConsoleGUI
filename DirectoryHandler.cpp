#include "DirectoryHandler.h"
#include <filesystem>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <sys/stat.h>
#include <unistd.h>


// Use the filesystem namespace for convenience
namespace fs = std::filesystem;

// Utility function to trim leading and trailing whitespace, unprintable, and non-ASCII characters
std::string DirectoryHandler::trim(const std::string& str) 
{
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


bool DirectoryHandler::isDirectory(const std::string& path)
{
    return fs::directory_entry(path).is_directory();
}

std::vector<std::string> DirectoryHandler::listDirectories(const std::string& path) 
{
    std::vector<std::string> directories;

    try 
    {
        for (const auto& entry : fs::directory_iterator(path)) 
        {
            //if (entry.is_directory()) 
            {
                std::string dirName = entry.path().filename().string();
                directories.push_back(dirName);
            }
        }
    } 
    catch (const fs::filesystem_error& err) 
    {
        std::cerr << "Error accessing directory: " << err.what() << std::endl;
    }

    return directories;
}

void DirectoryHandler::navigate(const std::string &initialPath)
{
    std::string currentPath = initialPath;
    std::vector<std::string> items;
    int selectedIndex = 0;
    bool running = true;

    while (running)
    {
        items.clear();
        items = listDirectories(currentPath);
        items.insert(items.begin(), ".."); // option to go back

        consoleHandler.displayItems(items, selectedIndex);

        char key = keyboardHandler.getKeyPress();

        if (key == 'q')
        {
            consoleHandler.disableRawMode();
            consoleHandler.clearScreen();
            running = false;
        }
        if (key == '\033')
        { // Escape sequence
            char seq[2];
            if (read(STDIN_FILENO, &seq[0], 1) == 0)
                break;
            if (read(STDIN_FILENO, &seq[1], 1) == 0)
                break;

            if (seq[0] == '[')
            {
                switch (seq[1])
                {
                case 'A': // Up arrow
                    if (selectedIndex > 0)
                    {
                        selectedIndex--;
                        //displayItems(items, selectedIndex);
                    }
                    break;
                case 'B': // Down arrow
                    if (selectedIndex < items.size() - 1)
                    {
                        selectedIndex++;
                        //displayItems(items, selectedIndex);
                    }
                    break;
                }
            }
        }
        if (key == '\n' || key == '\r')
        { // Enter key
            std::string newPath = currentPath + "/" + items[selectedIndex];
            
            if(isDirectory(newPath))
            {
                currentPath = newPath;
                selectedIndex = 0;
            }
            else
            {
                //if it is not a directory, check for file extensions
                std::cout << newPath << std::endl;
            }
            
        }
    }
}

