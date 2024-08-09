#ifndef IINPUTHANDLER_H
#define IINPUTHANDLER_H

#include <string>

class IInputHandler {
public:
    virtual ~IInputHandler() = default;

    // Reads a single key press from the user
    virtual char getKeyPress() = 0;

    // Reads a line of input from the user
    virtual std::string getLine() = 0;
};

#endif // IINPUTHANDLER_H
