#ifndef KEYBOARDHANDLER_H
#define KEYBOARDHANDLER_H

#include "IInputHandler.h"

class KeyboardHandler : public IInputHandler 
{
public:
    KeyboardHandler();

    // Implementations of InputHandler interface
    char getKeyPress() override;

};

#endif // KEYBOARDHANDLER_H
