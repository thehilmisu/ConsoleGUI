#include "ConsoleHandler.h"
#include <iostream>

int main() {
    ConsoleHandler consoleHandler;
    std::string homeDir = getenv("HOME");

    if (homeDir.empty()) {
        std::cerr << "Unable to determine the home directory." << std::endl;
        return 1;
    }

    consoleHandler.navigate(homeDir);
    return 0;
}