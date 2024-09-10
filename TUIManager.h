#ifndef TUIMANAGER_H
#define TUIMANAGER_H

#include <string>
#include <vector>
#include "UIElement.h"
#include <ncurses.h>

class TUIManager
{
public:
    template <typename T>
    void placeElement(T &element, int x, int y)
    {
        element.setPosition(x, y);
        elements.push_back(&element);
        element.draw();
    }

    void drawUI()
    {
        for (size_t i = 0; i < elements.size(); ++i)
        {
            elements[i]->draw(i == selectedElement);
        }
        refresh();
    }

    void handleInput()
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

    void initWindow()
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
    void endWindow()
    {
        endwin();
    }

private:
    std::vector<UIElement *> elements;
    size_t selectedElement = 0;

    void navigate(int direction)
    {
        selectedElement = (selectedElement + direction + elements.size()) % elements.size();
    }

    void handleMouse()
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
};

#endif