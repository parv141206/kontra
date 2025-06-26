#include "core/text.hpp"
#include "core/ansi.hpp"
#include "core/screen_buffer.hpp"
#include <string>
#include <algorithm>

#ifdef _WIN32
#undef min
#undef max
#endif

int Text::get_preferred_height(int width) const {
	if (width <= 0) return 1;
	std::string text_value = text();
	if (text_value.empty()) return 1;
	return (text_value.length() + width - 1) / width;
}


void Text::render(ScreenBuffer& buffer, int x, int y, int w, int h) const {
	std::string style_str = style.color + style.background_color;
	if (style.bold) style_str += ansi::BOLD;
	if (style.underline) style_str += ansi::UNDERLINE;
	if (style.italic) style_str += ansi::ITALIC;

	std::string text_value = text();
	int actual_text_lines = get_preferred_height(w);

	int text_pos = 0;
	for (int i = 0; i < h; ++i) {
		if (i < actual_text_lines) {
			for (int j = 0; j < w; ++j) {
				char char_to_draw = ' ';
				if (text_pos < text_value.length()) {
					char_to_draw = text_value[text_pos];
				}
				buffer.set_cell(x + j, y + i, std::string(1, char_to_draw), style_str);
				text_pos++;
			}
		}
		else {
			for (int j = 0; j < w; ++j) {
				buffer.set_cell(x + j, y + i, " ", ansi::RESET);
			}
		}
	}
}