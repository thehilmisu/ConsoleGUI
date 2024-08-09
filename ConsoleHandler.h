#ifndef CONSOLEHANDLER_H
#define CONSOLEHANDLER_H

#include "DirectoryHandler.h"
#include "KeyboardHandler.h"
#include <string>
#include <vector>

class ConsoleHandler {
public:
    ConsoleHandler();
    void navigate(const std::string& initialPath);

private:
    void displayItems(const std::vector<std::string>& items, int selectedIndex);
    void clearScreen();
    std::string trim(const std::string& str);
    DirectoryHandler directoryHandler;
    KeyboardHandler keyboardHandler;
};

#endif // CONSOLEHANDLER_H
