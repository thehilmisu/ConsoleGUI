#include "Label.h"

#include <iostream>

Label::Label(const std::string &text, int color_pair)
    : text(text), color_pair(color_pair), posX(0), posY(0) {}

void Label::draw(bool selected) const
{
    if (selected)
    {
        attron(A_REVERSE);
    }
    attron(COLOR_PAIR(color_pair));
    mvprintw(posY, posX, "%s", text.c_str());
    attroff(COLOR_PAIR(color_pair));
    if (selected)
    {
        attroff(A_REVERSE);
    }
}

void Label::setPosition(int x, int y)
{
    posX = x;
    posY = y;
}

bool Label::handleMouseClick(int mouseX, int mouseY)
{
    std::cout << mouseX << mouseY << std::endl;
    return false;
}

void Label::activate()
{
}