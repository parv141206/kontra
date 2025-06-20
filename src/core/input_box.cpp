#include "core/input_box.hpp"
#include "core/ansi.hpp"
#include <iostream>
#include <cctype>
#include <algorithm>
#ifdef _WIN32
#undef min
#undef max
#endif

int InputBox::get_preferred_height(int width) const {
    if (width <= 2) return 3; 

    int innerW = width - 2;

    if (!wrap) {
        return 3; 
    }

    // wrapped mode
    int lines = 1;
    int currentLineLength = 0;

    for (char c : text) {
        if (c == '\n') {
            lines++;
            currentLineLength = 0;
        }
        else {
            currentLineLength++;
            if (currentLineLength >= innerW) {
                lines++;
                currentLineLength = 0;
            }
        }
    }

    return lines + 2; // Adding 2 for top and bottom borders :3
}


void InputBox::set_active(bool is_active) {
    active = is_active;
}

bool InputBox::is_active() const {
    return active;
}

void InputBox::set_wrap_enabled(bool enabled) {
    wrap = enabled;
}

std::string InputBox::get_text() const {
    return text;
}

void InputBox::handle_input(char ch) {
    if (!active) return;

    switch (ch) {
    case '\b': case 127:  // backspace
        if (cursor > 0) {
            text.erase(cursor - 1, 1);
            cursor--;
        }
        break;
    case 27:  // ESC, optional exit
        break;
    case 75:  // LEFT arrow
        if (cursor > 0) cursor--;
        break;
    case 77:  // RIGHT arrow
        if (cursor < (int)text.size()) cursor++;
        break;
    default:
        if (std::isprint(static_cast<unsigned char>(ch))) {
            text.insert(cursor, 1, ch);
            cursor++;
        }
        break;
    }
}

void InputBox::render(int x, int y, int w, int h) const {
    int innerW = w - 2;
    int innerH = h - 2;

    // Top border
    ansi::move_cursor(y, x);
    std::cout << ansi::tl << std::string(innerW, ansi::h) << ansi::tr;

    // Content rows
    for (int row = 0; row < innerH; ++row) {
        ansi::move_cursor(y + 1 + row, x);
        std::cout << ansi::v;

        int start = 0;
        std::string line(innerW, ' ');

        if (wrap) {
            start = row * innerW;
            if (start < (int)text.size()) {
                std::string slice = text.substr(start, innerW);
                line.replace(0, slice.size(), slice);
            }
        }
        else {
            if (row == 0) {
                int offset = std::max(0, cursor - innerW);
                std::string visible = text.substr(offset, innerW);
                line.replace(0, visible.size(), visible);
            }
        }

        // Draws text line with cursor if it lands on this row
        if (active) {
            int cur_row = wrap ? (cursor / innerW) : 0;
            int cur_col = wrap ? (cursor % innerW) : (cursor >= innerW ? innerW - 1 : cursor);
            if (row == cur_row && cur_col < innerW) {
                line[cur_col] = '|';
            }
        }

        std::cout << line << ansi::v;
    }

    // Bottom border
    ansi::move_cursor(y + h - 1, x);
    std::cout << ansi::bl << std::string(innerW, ansi::h) << ansi::br;
}
