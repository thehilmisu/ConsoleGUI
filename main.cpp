#include "TUIManager.h"
#include "Label.h"
#include "Button.h"
#include "TableWidget.h"
#include "DropdownWidget.h"


int main() {
    
    TUIManager tuiManager;

    tuiManager.initWindow();

    auto button1 = std::make_unique<Button>("Button 1", []() { printw("\nButton 1 clicked!\n"); refresh(); }, RED_ON_BLACK);
    auto button2 = std::make_unique<Button>("Button 2", []() { printw("\nButton 2 clicked!\n"); refresh(); }, RED_ON_BLACK);
    auto label = std::make_unique<Label>("Test label", GREEN_ON_BLACK);

    // Position tablePos = {2, 2};
    // auto table = std::make_unique<TableWidget>(tablePos, 3);  //3 columns

    // table->setHeaders({"Header 1", "Header 2", "Header 3"});

    // // Add rows dynamically
    // table->addRow({"Item 1", "Item 2", "Item 3"});
    // table->addRow({"Item 4", "Item 5", "Item 6"});
    // table->addRow({"Item 7", "Item 8", "Item 9"});



    // tuiManager.placeElement(std::move(label), {0, 0});
    // tuiManager.placeElement(std::move(button1), {5, 5});
    // tuiManager.placeElement(std::move(button2), {5, 7});
    // tuiManager.placeElement(std::move(table), {5, 15});

    // Create a DropdownWidget
    Position tablePos = {2, 2};
    std::vector<std::string> dropdownOptions = {"Option 1", "Option 2", "Option 3", "Option 4"};
    auto drop = std::make_unique<DropdownWidget>(tablePos, dropdownOptions);

    // Add the DropdownWidget to the TUIManager
    tuiManager.placeElement(std::move(drop), {5, 5});


    tuiManager.drawUI();
    tuiManager.handleInput();

    tuiManager.endWindow();
    
    return 0;
}


