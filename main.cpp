#include "TUIManager.h"
#include "Label.h"
#include "Button.h"
#include "TableWidget.h"
#include "DropdownWidget.h"
#include "TabbedWidget.h"


int main() {
    
    TUIManager tuiManager;

    tuiManager.initWindow();

    Position btn1 = {2, 8};
    Position btn2 = {2, 10};
    Position labelpos = {0, 0};
    auto button1 = std::make_unique<Button>("Button 1", []() { printw("\nButton 1 clicked!\n"); refresh(); }, RED_ON_BLACK,btn1);
    auto button2 = std::make_unique<Button>("Button 2", []() { printw("\nButton 2 clicked!\n"); refresh(); }, RED_ON_BLACK,btn2);
    auto label = std::make_unique<Label>("Test label", GREEN_ON_BLACK, labelpos);

    Position tablePos = {40, 2};
    auto table = std::make_unique<TableWidget>(tablePos, 3);  //3 columns

    table->setHeaders({"Header 1", "Header 2", "Header 3"});

    // Add rows dynamically
    table->addRow({"Item 1", "Item 2", "Item 3"});
    table->addRow({"Item 4", "Item 5", "Item 6"});
    table->addRow({"Item 7", "Item 8", "Item 9"});

    // Create a DropdownWidget
    Position dropPos = {2, 2};
    std::vector<std::string> dropdownOptions = {"Option 1", "Option 2", "Option 3", "Option 4"};
    auto drop = std::make_unique<DropdownWidget>(dropPos, dropdownOptions);

    // Position tabbedWidgetPos = {2,2};
    // std::vector<std::string> tabLabels = {"Tab 1", "Tab 2", "Tab 3"};
    // auto tabs = std::make_unique<TabbedWidget>(tabbedWidgetPos, tabLabels);
    
    // tabs->addWidgetToTab(0,table.get());
    // tabs->addWidgetToTab(1,label.get());

    //tuiManager.placeElement(std::move(tabs));

    tuiManager.placeElement(std::move(label));
    tuiManager.placeElement(std::move(button1));
    tuiManager.placeElement(std::move(button2));
    tuiManager.placeElement(std::move(table));
    tuiManager.placeElement(std::move(drop));

    tuiManager.drawUI();
    tuiManager.handleInput();

    tuiManager.endWindow();
    
    return 0;
}


