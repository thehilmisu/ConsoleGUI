#ifndef TUIMANAGER_UI
#define TUIMANAGER_UI

#include <memory>
#include <vector>
#include "UIElement.h"
#include <ncurses.h>

class TUIManager {
public:
    template<typename T>
    void placeElement(std::unique_ptr<T> element, int x, int y) {
        element->setPosition(x, y);
        element->draw();
        elements.push_back(std::move(element));
    }

    void drawUI();
    void handleInput();
    void initWindow();
    void endWindow();

private:
    std::vector<std::unique_ptr<UIElement>> elements;
    size_t selectedElement = 0;

    void navigate(int direction);
    void handleMouse();
};

#endif