#include "DirectoryHandler.h"
#include <iostream>

int main() 
{
    DirectoryHandler directoryHandler;
    std::string homeDir = getenv("HOME");

    if (homeDir.empty()) 
    {
        std::cerr << "Unable to determine the home directory." << std::endl;
        return 1;
    }

    directoryHandler.navigate(homeDir);
    
    return 0;
}