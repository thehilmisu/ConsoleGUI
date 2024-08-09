#include "KeyboardHandler.h"
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <csignal>

KeyboardHandler::KeyboardHandler() : rawModeEnabled(false) {
    enableRawMode();
}

KeyboardHandler::~KeyboardHandler() {
    disableRawMode();
}

// Enables raw mode for the terminal to read key presses without waiting for newline
void KeyboardHandler::enableRawMode() {
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
void KeyboardHandler::disableRawMode() {
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

// Reads a single key press from the user
char KeyboardHandler::getKeyPress() {
    char c;
    ssize_t nread;
    while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
        if (nread == -1 && errno != EAGAIN) {
            perror("read");
            exit(EXIT_FAILURE);
        }
    }
    return c;
}

// Reads a line of input from the user
std::string KeyboardHandler::getLine() {
    disableRawMode(); // Switch back to normal mode
    std::string line;
    if (!std::getline(std::cin, line)) {
        // Handle EOF or error
        if (std::cin.eof()) {
            std::cout << "\nEOF received. Exiting.\n";
            exit(EXIT_SUCCESS);
        } else {
            std::cerr << "Error reading line.\n";
            exit(EXIT_FAILURE);
        }
    }
    enableRawMode(); // Switch back to raw mode
    return line;
}
