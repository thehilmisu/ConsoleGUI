#ifndef LABEL_H
#define LABEL_H

#include "UIElement.h"
#include <string>
#include <ncurses.h>

class Label : public UIElement
{
public:
    Label(const std::string &text, int color_pair = 0);
    virtual ~Label() = default;
    void draw(bool selected = false) const override;
    void setPosition(int x, int y) override;
    bool handleMouseClick(int mouseX, int mouseY) override;
    void activate() override;

private:
    std::string text;
    int color_pair;
    int posX, posY;
};

#endif