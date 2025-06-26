#include "core/text.hpp"
#include "core/ansi.hpp"
#include <iostream>
#include <string>
#include <algorithm> 
#ifdef _WIN32
#undef min
#undef max
#endif

int Text::get_preferred_height(int width) const {
    if (width <= 0) return 1;
    int lines = 0;
    std::string text_value = text();
    if (text_value.empty()) return 1;
    int current_pos = 0;
    while (current_pos < text_value.length()) {
        lines++;
        current_pos += width;
    }
    return lines;
}

void Text::render(int x, int y, int w, int h) const {
    std::string current_text = text();

    if (last_state.x == x && last_state.y == y && last_state.w == w && last_state.h == h && last_state.text == current_text) {
        return;
    }

    clear_area(last_state.x, last_state.y, last_state.w, last_state.h);

    int text_pos = 0;

    for (int i = 0; i < h; ++i) {
        ansi::move_cursor(y + i, x);

        if (text_pos < current_text.length()) {
            if (!style.color.empty()) std::cout << style.color;
            if (!style.background_color.empty()) std::cout << style.background_color;
            if (style.bold) std::cout << ansi::BOLD;
            if (style.underline) std::cout << ansi::UNDERLINE;
            if (style.italic) std::cout << ansi::ITALIC;

            int chars_on_line = std::min(w, (int)current_text.length() - text_pos);
            std::cout << current_text.substr(text_pos, chars_on_line);
            text_pos += chars_on_line;

            if (chars_on_line < w) {
                std::cout << std::string(w - chars_on_line, ' ');
            }
        }
        else {
            std::cout << ansi::RESET;
            std::cout << std::string(w, ' ');
        }
    }

    std::cout << ansi::RESET;

    last_state = { x, y, w, h, current_text };
}