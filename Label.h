#ifndef LABEL_H
#define LABEL_H

#include "UIElement.h"
#include <string>
#include <ncurses.h>


class Label : public UIElement {
public:
    Label(const std::string &text, int color_pair = 0)
        : text(text), color_pair(color_pair) {}

    void draw(bool selected = false) const override {
        if (selected) {
            attron(A_REVERSE);
        }
        attron(COLOR_PAIR(color_pair));
        mvprintw(posY, posX, "%s", text.c_str());
        attroff(COLOR_PAIR(color_pair));
        if (selected) {
            attroff(A_REVERSE);
        }
    }

    void setPosition(int x, int y) override {
        posX = x; posY = y;
    }
    bool handleMouseClick(int mouseX, int mouseY) override {
        return false;
    }
    void activate() override {

    } 

private:
    std::string text;
    int color_pair;
    int posX, posY;
};

#endif