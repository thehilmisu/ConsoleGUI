#include "TUIManager.h"
#include "Label.h"
#include "Button.h"



int main() {
    
    TUIManager tuiManager;

    tuiManager.initWindow();

    Label label("Hello, World!", 1);
    Button button1("Button 1", []() { printw("\nButton 1 clicked!\n"); refresh(); }, 2);
    Button button2("Button 2", []() { printw("\nButton 2 clicked!\n"); refresh(); }, 2);

    tuiManager.placeElement(label, 5, 5);
    tuiManager.placeElement(button1, 5, 7);
    tuiManager.placeElement(button2, 5, 9);

    tuiManager.drawUI();
    tuiManager.handleInput();

    tuiManager.endWindow();
    
    return 0;
}


