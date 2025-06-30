#include <iostream>
#include "core/button.hpp"
#include "core/ansi.hpp"

void Button::set_active(bool is_active) {
	if (active != is_active) {
		active = is_active;
	}
}

bool Button::is_active() const {
	return active;
}

void Button::click() {
	if (on_click_callback) on_click_callback();
}

void Button::render(ScreenBuffer& buffer, int x, int y, int w, int h) {
	Component::render(buffer, x, y, w, h); 
	std::string current_label = label();

	std::string style_str = is_active()
		? style.color_active + style.background_color_active
		: style.color + style.background_color;

	if (style.bold) style_str += ansi::BOLD;
	if (style.underline) style_str += ansi::UNDERLINE;
	if (style.italic) style_str += ansi::ITALIC;

	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j) {
			char char_to_draw = ' ';
			int text_pos = (i * w) + j;
			if (text_pos < current_label.length()) {
				char_to_draw = current_label[text_pos];
			}
			buffer.set_cell(x + j, y + i, std::string(1, char_to_draw), style_str);
		}
	}
}