#include "ConsoleHandler.h"
#include <iostream>
#include <unistd.h>
#include <algorithm>
#include <cctype>
#include <locale>
#include <string>
#include <termios.h>
#include <csignal>

ConsoleHandler::ConsoleHandler(): rawModeEnabled(false) 
{
    enableRawMode();
}

ConsoleHandler::~ConsoleHandler() 
{
    disableRawMode();
}

void ConsoleHandler::clearScreen()
{
    std::cout << "\033[2J\033[1;1H";
}

std::string ConsoleHandler::trim(const std::string &str)
{
    std::string trimmed = str;

    // Remove leading whitespace and unprintable characters
    trimmed.erase(trimmed.begin(), std::find_if(trimmed.begin(), trimmed.end(), [](unsigned char ch)
                                                { return !std::isspace(ch) && std::isprint(ch); }));

    // Remove trailing whitespace and unprintable characters
    trimmed.erase(std::find_if(trimmed.rbegin(), trimmed.rend(), [](unsigned char ch)
                               { return !std::isspace(ch) && std::isprint(ch); })
                      .base(),
                  trimmed.end());

    return trimmed;
}

// Enables raw mode for the terminal to read key presses without waiting for newline
void ConsoleHandler::enableRawMode() 
{
    if (rawModeEnabled) return; // Already enabled

    termios term;
    if (tcgetattr(STDIN_FILENO, &term) == -1) {
        perror("tcgetattr");
        exit(EXIT_FAILURE);
    }

    // Save original terminal attributes for restoration later
    static termios originalTerm = term;

    // Ensure terminal settings are restored on program exit
    static bool restoreOnExitSet = false;
    if (!restoreOnExitSet) {
        atexit([]() {
            tcsetattr(STDIN_FILENO, TCSAFLUSH, &originalTerm);
        });
        restoreOnExitSet = true;
    }

    termios raw = term;
    raw.c_lflag &= ~(ECHO | ICANON | ISIG); // Disable echoing, canonical mode, and signals
    raw.c_iflag &= ~(IXON | ICRNL | BRKINT | INPCK | ISTRIP); // Disable specific input flags
    raw.c_oflag &= ~(OPOST); // Disable output processing
    raw.c_cflag |= (CS8); // Set character size to 8 bits

    raw.c_cc[VMIN] = 0;  // Minimum number of bytes of input before read() returns
    raw.c_cc[VTIME] = 1; // Maximum time to wait before read() returns

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
        perror("tcsetattr");
        exit(EXIT_FAILURE);
    }

    rawModeEnabled = true;
}

// Restores the terminal to its previous state
void ConsoleHandler::disableRawMode() 
{
    if (!rawModeEnabled) return; // Already disabled

    termios term;
    if (tcgetattr(STDIN_FILENO, &term) == -1) {
        perror("tcgetattr");
        exit(EXIT_FAILURE);
    }

    term.c_lflag |= (ECHO | ICANON | ISIG);
    term.c_iflag |= (IXON | ICRNL | BRKINT | INPCK | ISTRIP);
    term.c_oflag |= (OPOST);
    term.c_cflag &= ~(CS8);

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &term) == -1) {
        perror("tcsetattr");
        exit(EXIT_FAILURE);
    }

    rawModeEnabled = false;
}


void ConsoleHandler::displayItems(const std::vector<std::string> &items, int selectedIndex)
{
    clearScreen();
    disableRawMode();

    for (size_t i = 0; i < items.size(); ++i)
    {
        if (i == selectedIndex)
        {
            std::cout << "> " << trim(items[i]) << std::endl; // Highlight the selected item
        }
        else
        {
            std::cout << "  " << trim(items[i]) << std::endl;
        }
    }

    enableRawMode();
}
