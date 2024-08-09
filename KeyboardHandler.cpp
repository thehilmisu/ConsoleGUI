#include "KeyboardHandler.h"
#include <iostream>
#include <unistd.h>


KeyboardHandler::KeyboardHandler() {}

// Reads a single key press from the user
char KeyboardHandler::getKeyPress() 
{
    char c;
    ssize_t nread;
    while ((nread = read(STDIN_FILENO, &c, 1)) != 1) 
    {
        if (nread == -1 && errno != EAGAIN) 
        {
            perror("read");
            exit(EXIT_FAILURE);
        }
    }
    return c;
}
