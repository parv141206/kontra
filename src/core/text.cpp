#include "core/text.hpp"
#include "core/ansi.hpp"
#include <iostream>
#include <string>
#include <algorithm> 

/*
* @brief Renders the text at the specified position and size,
*        handling multi-line wrapping if the text exceeds the width.
*
* @param x The x-coordinate where rendering starts.
* @param y The y-coordinate where rendering starts.
* @param w The width of the area to render.
* @param h The height of the area to render.
*
*/
void Text::render(int x, int y, int w, int h) const
{
    std::string text_value = text();
    if (w <= 0 || h <= 0 || text_value.empty()) {
        return;
    }

    // styles
    if (!style.color.empty()) std::cout << style.color;
    if (!style.backgroundColor.empty()) std::cout << style.backgroundColor;
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