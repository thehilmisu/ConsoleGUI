#ifndef UIELEMENT_H
#define UIELEMENT_H

class UIElement {
public:
    virtual void draw(bool selected = false) const = 0;
    virtual void setPosition(int x, int y) = 0;
    virtual bool handleMouseClick(int mouseX, int mouseY) = 0;
    virtual void activate() = 0;
    virtual ~UIElement() = default;

};

#endif //UIElement