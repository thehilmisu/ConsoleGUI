#ifndef DIRECTORYHANDLER_H
#define DIRECTORYHANDLER_H

#include <vector>
#include <string>
#include <glob.h>

class DirectoryHandler {
public:
    // Function to list directories in the given path
    std::vector<std::string> listDirectories(const std::string& path);
    std::string trim(const std::string& str);
    void test();
};

#endif // DIRECTORYHANDLER_H
