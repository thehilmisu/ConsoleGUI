#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <ncurses.h>
#include <vector>
#include <string>
#include "UIElement.h"  

class TableWidget : public UIElement {
public:
    TableWidget(Position pos, int cols)
        : position(pos), cols(cols), cellWidth(15), padding(3) {
        selectedRow = 0;
        selectedCol = 0;
    }

    void setHeaders(const std::vector<std::string> &headerLabels) {
        headers = headerLabels;
        if (headers.size() != cols) {
            throw std::runtime_error("Header labels count does not match the number of columns.");
        }
    }

    void addRow(const std::vector<std::string> &rowData) {
        if (rowData.size() != cols) {
            throw std::runtime_error("Row data does not match the number of columns.");
        }
        content.push_back(rowData);
    }

    void removeRow(int rowIndex) {
        if (rowIndex >= 0 && rowIndex < content.size()) {
            content.erase(content.begin() + rowIndex);
            if (selectedRow >= content.size()) {
                selectedRow = content.size() - 1;
            }
        }
    }

    void setItem(int row, int col, const std::string &text) {
        if (row < content.size() && col < cols) {
            content[row][col] = text;
        }
    }

    void draw(bool selected = false) const override {
        drawBorders();
        drawHeaders();
        drawCells(selected);
        refresh(); // Refresh the screen after drawing
    }

    void setPosition(Position pos) override {
        position = pos;
    }

    bool handleMouseClick(Position mouse_pos) override {
        int row = (mouse_pos.y - position.y - 1);  // Adjust for header row
        int col = (mouse_pos.x - position.x) / cellWidth;
        if (row >= 0 && row < content.size() && col >= 0 && col < cols) {
            selectedRow = row;
            selectedCol = col;
            draw(true);
            return true;
        }
        return false;
    }

    void activate() override {
        editItem("Activated");
    }

    void navigate(int dRow, int dCol) {
        if (!content.empty()) {
            selectedRow = (selectedRow + dRow + content.size()) % content.size();
            selectedCol = (selectedCol + dCol + cols) % cols;
            draw(true);
        }
    }

    void editItem(const std::string &text) {
        if (!content.empty()) {
            content[selectedRow][selectedCol] = text;
            draw(true);
        }
    }

private:
    Position position;  // Position in the terminal window
    int cols;
    int cellWidth;
    int padding;
    int selectedRow, selectedCol;
    std::vector<std::vector<std::string>> content;
    std::vector<std::string> headers;

    void drawHeaders() const {
        for (int j = 0; j < cols; ++j) {
            int x = position.x + j * cellWidth + padding;
            mvprintw(position.y, x, "%-*s", cellWidth - 2 * padding - 1, headers[j].c_str());
        }
    }

    void drawCells(bool selected) const {
        for (size_t i = 0; i < content.size(); ++i) {
            for (int j = 0; j < cols; ++j) {
                drawCell(i + 1, j, (i == selectedRow && j == selectedCol) ? selected : false); // Shift by 1 to accommodate headers
            }
        }
    }

    void drawCell(int row, int col, bool selected) const {
        int x = position.x + col * cellWidth + padding;
        int y = position.y + row;
        std::string text = content[row - 1][col]; // Adjust for header row

        // Draw text within the cell
        if (selected) {
            attron(COLOR_PAIR(1));
            mvprintw(y, x, "%-*s", cellWidth - 2 * padding - 1, text.c_str());
            attroff(COLOR_PAIR(1));
        } else {
            attron(COLOR_PAIR(2));
            mvprintw(y, x, "%-*s", cellWidth - 2 * padding - 1, text.c_str());
            attroff(COLOR_PAIR(2));
        }
    }

    void drawBorders() const {
        // Draw horizontal lines
        for (int i = 0; i <= content.size(); ++i) {  // Adjust to include the header row
            int y = position.y + i + 1;
            mvhline(y, position.x, '-', cols * cellWidth);
        }

        // Draw vertical lines
        for (int j = 0; j <= cols; ++j) {
            int x = position.x + j * cellWidth;
            mvvline(position.y, x, '|', content.size() + 1);
        }

        // Draw corner intersections
        for (int i = 0; i <= content.size(); ++i) {
            for (int j = 0; j <= cols; ++j) {
                int x = position.x + j * cellWidth;
                int y = position.y + i + 1;
                mvaddch(y, x, '+');
            }
        }
    }
};

#endif // TABLEWIDGET_H
