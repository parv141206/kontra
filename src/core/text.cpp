#include "core/text.hpp"
#include "core/ansi.hpp"
#include <iostream>
#include <string>
#include <algorithm> 

int Text::get_preferred_height(int width) const {
    if (width <= 0) return 1;

    int lines = 1;
    int currentLineLength = 0;
    std::string text_value = text();
    for (char c : text_value) {
        if (c == '\n') {
            lines++;
            currentLineLength = 0;
        }
        else {
            currentLineLength++;
            if (currentLineLength >= width) {
                lines++;
                currentLineLength = 0;
            }
        }
    }
    return lines;
}

void Text::render(int x, int y, int w, int h) const
{
    std::string text_value = text();
    if (w <= 0 || h <= 0 || text_value.empty()) {
        return;
    }

    // styles
    if (!style.color.empty()) std::cout << style.color;
    if (!style.background_color.empty()) std::cout << style.background_color;
    if (style.bold) std::cout << ansi::BOLD;
    if (style.underline) std::cout << ansi::UNDERLINE;
    if (style.italic) std::cout << ansi::ITALIC;

    int current_y = y; 
    int text_pos = 0; 

    while (text_pos < text_value.length() && (current_y - y) < h) {
        ansi::move_cursor(current_y, x);
        int chars_on_line = (w < (int)(text_value.length() - text_pos)) ? w : (int)(text_value.length() - text_pos);

        std::cout << text_value.substr(text_pos, chars_on_line);

        if (chars_on_line < w) {
            std::cout << std::string(w - chars_on_line, ' ');
        }

        text_pos += chars_on_line;

        current_y++;
    }

    std::cout << ansi::RESET;

	// This is just filling up the remaining space with empty lines if needed, couldnt find a better way to do this :/
    while ((current_y - y) < h) {
        ansi::move_cursor(current_y, x);
        std::cout << std::string(w, ' '); 
        current_y++;
    }
}