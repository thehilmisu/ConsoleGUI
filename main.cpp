// main.cpp
#include "TUIManager.h"
#include "Label.h"
#include "Button.h"
#include "TableWidget.h"
#include "DropdownWidget.h"
#include <iostream>

void onOptionChanged(const std::string &text, UIElement* element) {
    element->setText(text);
}

int main() {

    // Instantiate TUIManager globally to access it in the callback function
    TUIManager tuiManager;
    
    // Initialize the TUIManager and ncurses
    tuiManager.initWindow();

    // Create buttons
    Position btn1Pos = {2, 8};
    Position btn2Pos = {2, 10};
    auto button1 = std::make_shared<Button>("Button 1", []() { printw("\nButton 1 clicked!\n"); refresh(); }, RED_ON_BLACK, btn1Pos);
    auto button2 = std::make_shared<Button>("Button 2", []() { printw("\nButton 2 clicked!\n"); refresh(); }, RED_ON_BLACK, btn2Pos);



    // Create a Label object globally to access it in the callback function
    Position labelPos = {0, 0};
    auto label = std::make_shared<Label>("Test label", GREEN_ON_BLACK, labelPos);

    // Create a TableWidget
    Position tablePos = {40, 2};
    auto table = std::make_shared<TableWidget>(tablePos, 3);  // 3 columns
    table->setHeaders({"Header 1", "Header 2", "Header 3"});
    table->addRow({"Item 1", "Item 2", "Item 3"});
    table->addRow({"Item 4", "Item 5", "Item 6"});
    table->addRow({"Item 7", "Item 8", "Item 9"});

    // Create a DropdownWidget
    Position dropPos = {2, 2};
    std::vector<std::string> dropdownOptions = {"Option 1", "Option 2", "Option 3", "Option 4"};
    auto dropdown = std::make_shared<DropdownWidget>(dropPos, dropdownOptions);

    // Connect the onDropdownOptionSelected function to the dropdown's onOptionSelected signal
    dropdown->onOptionsSelected.connect([label](const std::string& option) {
        //label->setText(option);
        onOptionChanged(option, label.get());
    });

    // Place UI elements into the TUIManager
    tuiManager.placeElement(label);           // Place the label
    tuiManager.placeElement(button1);        // Place the first button
    tuiManager.placeElement(button2);        // Place the second button
    tuiManager.placeElement(table);          // Place the table
    tuiManager.placeElement(dropdown);       // Place the dropdown

    // Draw the UI and start handling user input
    tuiManager.drawUI();
    tuiManager.handleInput();

    // End the ncurses window
    tuiManager.endWindow();

    return 0;
}
