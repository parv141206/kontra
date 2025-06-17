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
    if (w <= 0 || h <= 0 || text.empty()) {
        return;
    }

    int current_y = y; 
    int text_pos = 0; 

    while (text_pos < text.length() && (current_y - y) < h) { 
        ansi::move_cursor(current_y, x);
        int chars_on_line = (w < (int)(text.length() - text_pos)) ? w : (int)(text.length() - text_pos);

        std::cout << text.substr(text_pos, chars_on_line);

        if (chars_on_line < w) {
            std::cout << std::string(w - chars_on_line, ' ');
        }

        text_pos += chars_on_line;

        current_y++;
    }

    while ((current_y - y) < h) {
        ansi::move_cursor(current_y, x);
        std::cout << std::string(w, ' '); 
        current_y++;
    }
}