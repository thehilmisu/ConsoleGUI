#ifndef CONSOLEHANDLER_H
#define CONSOLEHANDLER_H

#include <string>
#include <vector>

class ConsoleHandler 
{
public:
    ConsoleHandler();
    ~ConsoleHandler();
    void displayItems(const std::vector<std::string>& items, int selectedIndex);
    void clearScreen();
    void enableRawMode();
    void disableRawMode();

private:
    bool rawModeEnabled;
    std::string trim(const std::string& str);
   
};

#endif // CONSOLEHANDLER_H
