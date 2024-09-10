#ifndef BUTTON_H
#define BUTTON_H

#include "UIElement.h"
#include <string>
#include <functional>
#include <ncurses.h>


class Button : public UIElement {
public:
    Button(const std::string &label, std::function<void()> onClick, int color_pair = 0)
        : label(label), onClick(onClick), color_pair(color_pair) {}

    void draw(bool selected = false) const override {
        if (selected) {
            attron(A_REVERSE);
        }
        attron(COLOR_PAIR(color_pair));
        mvprintw(posY, posX, "[ %s ]", label.c_str());
        attroff(COLOR_PAIR(color_pair));
        if (selected) {
            attroff(A_REVERSE);
        }
    }

    void activate() override {
        if (onClick) {
            onClick();
        }
    }

    bool handleMouseClick(int mouseX, int mouseY) override {
        int length = label.length() + 4; // 4 for "[ ]" around the label
        if (mouseY == posY && mouseX >= posX && mouseX < posX + length) {
            activate();
            return true;
        }
        return false;
    }

    void setPosition(int x, int y) override {
        posX = x; posY = y;
    }

private:
    std::string label;
    std::function<void()> onClick;
    int color_pair;
    int posX, posY;
};

#endif