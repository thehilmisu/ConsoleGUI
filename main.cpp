#include "TUIManager.h"
#include "Label.h"
#include "Button.h"



int main() {
    
    TUIManager tuiManager;

    tuiManager.initWindow();

    // Create UI elements and add them to the manager
    auto button1 = std::make_unique<Button>("Button 1", []() { printw("\nButton 1 clicked!\n"); refresh(); }, 2);
    auto button2 = std::make_unique<Button>("Button 2", []() { printw("\nButton 2 clicked!\n"); refresh(); }, 2);

    tuiManager.placeElement(std::move(button1), 5, 5);
    tuiManager.placeElement(std::move(button2), 5, 7);

    tuiManager.drawUI();
    tuiManager.handleInput();

    tuiManager.endWindow();
    
    return 0;
}


