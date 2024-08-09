#ifndef DIRECTORYHANDLER_H
#define DIRECTORYHANDLER_H

#include <vector>
#include <string>
#include "KeyboardHandler.h"
#include "ConsoleHandler.h"

class DirectoryHandler 
{
public:
    std::vector<std::string> listDirectories(const std::string& path);
    void navigate(const std::string &initialPath);
    bool isDirectory(const std::string& path);
   
private:
    KeyboardHandler keyboardHandler;
    ConsoleHandler consoleHandler;
    std::string trim(const std::string& str);
};

#endif // DIRECTORYHANDLER_H
