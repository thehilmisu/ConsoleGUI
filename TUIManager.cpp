#include "TUIManager.h"


void TUIManager::drawUI() {
    for (size_t i = 0; i < elements.size(); ++i) {
        elements[i]->draw(i == selectedElement);
    }
    refresh();
}

void TUIManager::handleInput()
{
    int ch;
    while ((ch = getch()) != 'q')
    {
        switch (ch)
        {
        case KEY_UP:
            navigate(-1);
            break;
        case KEY_DOWN:
            navigate(1);
            break;
        case '\n': // Enter key
            elements[selectedElement]->activate();
            break;
        case KEY_MOUSE:
            handleMouse();
            break;
        }
        drawUI();
    }
}

void TUIManager::initWindow()
{
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);

    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
}

void TUIManager::endWindow()
{
    endwin();
}

void TUIManager::navigate(int direction)
{
    selectedElement = (selectedElement + direction + elements.size()) % elements.size();
}

void TUIManager::handleMouse()
{
    MEVENT event;
    if (getmouse(&event) == OK)
    {
        for (size_t i = 0; i < elements.size(); ++i)
        {
            if (elements[i]->handleMouseClick(event.x, event.y))
            {
                selectedElement = i;
                break;
            }
        }
    }
}
