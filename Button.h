#ifndef BUTTON_H
#define BUTTON_H

#include "UIElement.h"
#include <string>
#include <functional>
#include <ncurses.h>

class Button : public UIElement
{
public:
    Button(const std::string &label, std::function<void()> onClick, int color_pair = 0);
    virtual ~Button() = default;
    void draw(bool selected = false) const override;
    void activate() override;
    bool handleMouseClick(int mouseX, int mouseY) override;
    void setPosition(int x, int y) override;

private:
    std::string label;
    std::function<void()> onClick;
    int color_pair;
    int posX, posY; // Store the position within the Button class itself
};

#endif
