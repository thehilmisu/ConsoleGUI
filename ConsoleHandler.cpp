#include "ConsoleHandler.h"
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <algorithm>
#include <cctype>
#include <locale>
#include <string>

ConsoleHandler::ConsoleHandler()
{
    // Constructor implementation (if needed)
}

void ConsoleHandler::clearScreen()
{
    std::cout << "\033[2J\033[1;1H";
}

std::string ConsoleHandler::trim(const std::string &str)
{
    std::string trimmed = str;

    // Remove leading whitespace and unprintable characters
    trimmed.erase(trimmed.begin(), std::find_if(trimmed.begin(), trimmed.end(), [](unsigned char ch)
                                                { return !std::isspace(ch) && std::isprint(ch); }));

    // Remove trailing whitespace and unprintable characters
    trimmed.erase(std::find_if(trimmed.rbegin(), trimmed.rend(), [](unsigned char ch)
                               { return !std::isspace(ch) && std::isprint(ch); })
                      .base(),
                  trimmed.end());

    return trimmed;
}

void ConsoleHandler::displayItems(const std::vector<std::string> &items, int selectedIndex)
{
    clearScreen();
    keyboardHandler.disableRawMode();

    for (size_t i = 0; i < items.size(); ++i)
    {
        if (i == selectedIndex)
        {
            std::cout << "> " << trim(items[i]) << std::endl; // Highlight the selected item
        }
        else
        {
            std::cout << "  " << trim(items[i]) << std::endl;
        }
    }

    keyboardHandler.enableRawMode();
}

void ConsoleHandler::navigate(const std::string &initialPath)
{
    std::string currentPath = initialPath;
    std::vector<std::string> items;
    int selectedIndex = 0;
    bool running = true;

    while (running)
    {
        items.clear();
        items = directoryHandler.listDirectories(currentPath);
        items.insert(items.begin(), ".."); // option to go back

        displayItems(items, selectedIndex);

        char key = keyboardHandler.getKeyPress();

        if (key == 'q')
        {
            keyboardHandler.disableRawMode();
            clearScreen();
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
            std::string selectedItem = items[selectedIndex];
            currentPath = currentPath + "/" + selectedItem;
            selectedIndex = 0;
        }
    }
}
