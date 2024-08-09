#ifndef KEYBOARDHANDLER_H
#define KEYBOARDHANDLER_H

#include "IInputHandler.h"

class KeyboardHandler : public IInputHandler {
public:
    KeyboardHandler();
    ~KeyboardHandler();

    // Implementations of InputHandler interface
    char getKeyPress() override;
    std::string getLine() override;
    void enableRawMode();
    void disableRawMode();

private:
    bool rawModeEnabled;
};

#endif // KEYBOARDHANDLER_H
