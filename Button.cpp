#include "Button.h"

Button::Button(const std::string &label, std::function<void()> onClick, int color_pair)
    : label(label), onClick(onClick), color_pair(color_pair), posX(0), posY(0)
{
}

void Button::draw(bool selected) const
{
    if (selected)
    {
        attron(A_REVERSE);
    }
    attron(COLOR_PAIR(color_pair));
    mvprintw(posY, posX, "[ %s ]", label.c_str());
    attroff(COLOR_PAIR(color_pair));
    if (selected)
    {
        attroff(A_REVERSE);
    }
}

void Button::activate()
{
    if (onClick)
    {
        onClick();
    }
}

bool Button::handleMouseClick(int mouseX, int mouseY)
{
    int length = label.length() + 4; // 4 for "[ ]" around the label
    if (mouseY == posY && mouseX >= posX && mouseX < posX + length)
    {
        activate();
        return true;
    }
    return false;
}

void Button::setPosition(int x, int y)
{
    posX = x;
    posY = y;
}
