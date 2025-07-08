#include "core/text.hpp"
#include "core/ansi.hpp"
#include "core/screen_buffer.hpp"
#include <string>
#include <vector>
#include <algorithm>

#ifdef _WIN32
#undef min
#undef max
#endif

std::vector<std::string> wrap_text(const std::string& text, int width) {
    if (width <= 0) {
        return { text }; 
    }

    std::vector<std::string> lines;
    std::string current_line;
    std::string word;

    for (char c : text) {
        if (c == '\n') {
            current_line += word;
            lines.push_back(current_line);
            current_line.clear();
            word.clear();
            continue;
        }

        if (isspace(c)) {
            current_line += word;
            word.clear();
            current_line += c;
        }
        else {
            word += c;
        }

        if (current_line.length() + word.length() > (size_t)width) {
            lines.push_back(current_line);
            current_line.clear();
        }
    }
    current_line += word;
    lines.push_back(current_line);

    return lines;
}


int Text::get_preferred_height(int width) const {
    if (width <= 0) return 1;
    std::string text_value = text();
    if (text_value.empty()) return 1;

    return wrap_text(text_value, width).size();
}


void Text::render(ScreenBuffer& buffer, int x, int y, int w, int h) {
    Component::render(buffer, x, y, w, h); 

    std::string text_style = style.color + style.background_color;
    if (style.bold) text_style += ansi::BOLD;
    if (style.underline) text_style += ansi::UNDERLINE;
    if (style.italic) text_style += ansi::ITALIC;

    std::string bg_only_style = style.background_color.empty()
        ? ansi::RESET
        : style.background_color;

    std::string text_to_render = text();

    int text_idx = 0;
    for (int i = 0; i < h; ++i) { 
        for (int j = 0; j < w; ++j) { 
            if (text_idx < text_to_render.length()) {
                char current_char = text_to_render[text_idx];

                if (current_char == '\n') {
                    text_idx++;
                    for (int k = j; k < w; ++k) {
                        buffer.set_cell(x + k, y + i, " ", bg_only_style);
                    }
                    goto next_line;
                }

                buffer.set_cell(x + j, y + i, std::string(1, current_char), text_style);
                text_idx++;
            }
            else {
                buffer.set_cell(x + j, y + i, " ", bg_only_style);
            }
        }
    next_line:;
    }
}
