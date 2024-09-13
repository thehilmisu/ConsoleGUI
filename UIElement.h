#ifndef UIELEMENT_H
#define UIELEMENT_H

#include "Signal.h"  // Include the Signal class for signal support
#include <string>

struct Position {
    int x;
    int y;
};

class UIElement
{
public:
    virtual ~UIElement() = default;
    virtual void draw(bool selected = false) const = 0;
    virtual void setPosition(Position pos) = 0;
    virtual bool handleMouseClick(Position mouse_pos) = 0;
    virtual void activate() = 0;
    virtual void setText(const std::string& text) {};

protected:
    UIElement() = default;

    // Common signals can be declared here if needed
    // For example, a signal for when the element is activated
    // Signal<> onActivated;
};

#endif // UIELEMENT_H
