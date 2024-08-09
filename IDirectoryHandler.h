#ifndef IDIRECTORYHANDLER_H
#define IDIRECTORYHANDLER_H

#include <vector>
#include <string>

class IDirectoryHandler 
{
public:
    virtual std::vector<std::string> listDirectories(const std::string& path) = 0;
    virtual ~IDirectoryHandler() = default;
};

#endif // IDIRECTORYHANDLER_H