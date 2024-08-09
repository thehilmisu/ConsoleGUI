#include <iostream>
#include <vector>
#include <sstream>
#include <termios.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

// Terminal manipulation functions
void clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

void moveCursorToLineStart(int line) {
    std::cout << "\033[" << line << ";1H";
}

void clearLine(int line) {
    moveCursorToLineStart(line);
    std::cout << "\033[K";
}

void hideCursor() {
    std::cout << "\033[?25l";
}

void showCursor() {
    std::cout << "\033[?25h";
}

// Key press handling
char getKeyPress() {
    struct termios oldt, newt;
    char ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ch = std::cin.get();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}

// Printing functions
void printMenu() {
    int menuLine = 13; // Assuming the list starts from line 1 and has 12 lines max
    clearLine(menuLine);
    moveCursorToLineStart(menuLine);
    std::cout << "Open File (O)  Exit (q)";
}

void printLines(const std::vector<std::string>& lines, int startIndex, int selectedIndex, int offset) {
    for (int i = 0; i < 6; ++i) {
        if (startIndex + i >= lines.size()) {
            clearLine(i + offset);
            continue;
        }
        clearLine(i + offset);
        moveCursorToLineStart(i + offset);
        if (startIndex + i == selectedIndex) {
            std::cout << "> " << lines[startIndex + i] << std::endl;
        } else {
            std::cout << "  " << lines[startIndex + i] << std::endl;
        }
    }
    std::cout.flush();
}

void printDetail(const std::string& detail, int startLine) {
    std::istringstream stream(detail);
    std::string line;
    int lineNum = startLine;

    while (std::getline(stream, line)) {
        moveCursorToLineStart(lineNum);
        clearLine(lineNum);
        std::cout << line << std::endl;
        ++lineNum;
    }
    std::cout.flush();
}

void initializeTerminal() {
    clearScreen();
    hideCursor();
}

void resetTerminal() {
    showCursor();
}

std::vector<std::string> listHomeDirectory() {
    std::vector<std::string> files;
    const char* homeDir = getenv("HOME");

    if (homeDir) {
        DIR* dir = opendir(homeDir);
        if (dir) {
            struct dirent* entry;
            while ((entry = readdir(dir)) != nullptr) {
                files.push_back(entry->d_name);
            }
            closedir(dir);
        }
    }

    return files;
}

void handleFileMenu() {
    // Clear the screen except for the bottom menu
    for (int i = 1; i < 13; ++i) {
        clearLine(i);
    }

    // List the files and folders in the home directory
    std::vector<std::string> files = listHomeDirectory();
    int selectedIndex = 0;
    int startIndex = 0;

    printLines(files, startIndex, selectedIndex, 1); // Offset by 1 to fit in the screen

    bool selecting = true;

    while (selecting) {
        char ch = getKeyPress();
        switch (ch) {
            case '\033': // Escape sequence
                if (std::cin.get() == '[') {
                    switch (std::cin.get()) {
                        case 'A': // Up arrow
                            if (selectedIndex > 0) {
                                --selectedIndex;
                                if (selectedIndex < startIndex) {
                                    startIndex = selectedIndex;
                                }
                            }
                            break;
                        case 'B': // Down arrow
                            if (selectedIndex < files.size() - 1) {
                                ++selectedIndex;
                                if (selectedIndex >= startIndex + 6) {
                                    startIndex = selectedIndex - 5;
                                }
                            }
                            break;
                    }
                }
                break;
            case '\n': // Enter key
                selecting = false;
                clearScreen();
                printMenu();
                moveCursorToLineStart(1);
                std::cout << "Selected: " << files[selectedIndex] << std::endl;
                break;
            case 'q': // 'q' key to exit selection
                selecting = false;
                clearScreen();
                printMenu();
                break;
        }
        printLines(files, startIndex, selectedIndex, 1);
    }
}

void runApplication(const std::vector<std::string>& lines, const std::vector<std::string>& details) {
    int selectedIndex = 0;
    int startIndex = 0;
    bool running = true;

    initializeTerminal();
    printLines(lines, startIndex, selectedIndex, 1); // Offset by 1 line
    printMenu();

    while (running) {
        char ch = getKeyPress();
        switch (ch) {
            case '\033': // Escape sequence
                if (std::cin.get() == '[') {
                    switch (std::cin.get()) {
                        case 'A': // Up arrow
                            if (selectedIndex > 0) {
                                --selectedIndex;
                                if (selectedIndex < startIndex) {
                                    startIndex = selectedIndex;
                                }
                            }
                            break;
                        case 'B': // Down arrow
                            if (selectedIndex < lines.size() - 1) {
                                ++selectedIndex;
                                if (selectedIndex >= startIndex + 6) {
                                    startIndex = selectedIndex - 5;
                                }
                            }
                            break;
                    }
                }
                break;
            case '\n': // Enter key
                clearScreen();
                printLines(lines, startIndex, selectedIndex, 1);
                printDetail(details[selectedIndex], 8); // Print detail below the lines
                printMenu();
                break;
            case 'q': // 'q' key to quit
                running = false;
                break;
            case 'O': // 'O' key to open file
            case 'o': // Support for lowercase as well
                handleFileMenu();
                break;
        }
        printLines(lines, startIndex, selectedIndex, 1);
    }

    resetTerminal();
}

int main() {
    std::vector<std::string> lines{
        "Line 1: Hello World",
        "Line 2: Welcome to C++",
        "Line 3: This is a test",
        "Line 4: Navigate with arrow keys",
        "Line 5: Press Enter to select",
        "Line 6: Press q to exit",
        "Line 7: Additional Line 1",
        "Line 8: Additional Line 2",
        "Line 9: Additional Line 3",
        "Line 10: Additional Line 4",
        "Line 11: Additional Line 5",
        "Line 12: Additional Line 6"
    };

    std::vector<std::string> details{
        "Detailed message for Line 1: Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec vel nunc euismod, pharetra justo non, pretium massa.",
        "Detailed message for Line 2: Sed sit amet eros vitae sem vehicula interdum. Cras euismod risus eu eros aliquam, nec fermentum augue ullamcorper.",
        "Detailed message for Line 3: Quisque in libero eu felis volutpat tempus. Nam cursus neque sit amet magna vestibulum, nec consectetur libero pulvinar.",
        "Detailed message for Line 4: Integer euismod nulla ut augue ultricies, a interdum felis sagittis. Vivamus vel magna et dui condimentum tincidunt.",
        "Detailed message for Line 5: Donec tincidunt nulla ac augue bibendum, at pharetra purus posuere. Pellentesque habitant morbi tristique senectus et netus.",
        "Detailed message for Line 6: Nulla facilisi. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia curae; Vivamus at volutpat lacus.",
        "Detailed message for Line 7: Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec vel nunc euismod, pharetra justo non, pretium massa.",
        "Detailed message for Line 8: Sed sit amet eros vitae sem vehicula interdum. Cras euismod risus eu eros aliquam, nec fermentum augue ullamcorper.",
        "Detailed message for Line 9: Quisque in libero eu felis volutpat tempus. Nam cursus neque sit amet magna vestibulum, nec consectetur libero pulvinar.",
        "Detailed message for Line 10: Integer euismod nulla ut augue ultricies, a interdum felis sagittis. Vivamus vel magna et dui condimentum tincidunt.",
        "Detailed message for Line 11: Donec tincidunt nulla ac augue bibendum, at pharetra purus posuere. Pellentesque habitant morbi tristique senectus et netus.",
        "Detailed message for Line 12: Nulla facilisi. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia curae; Vivamus at volutpat lacus."
    };

    runApplication(lines, details);

    return 0;
}
