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

void Button::render(int x, int y, int w, int h) const {
	std::string current_label = label();
	bool current_active = is_active();

	if (last_state.x == x && last_state.y == y && last_state.w == w && last_state.h == h && last_state.label == current_label && last_state.active == current_active) {
		return;
	}

	clear_area(last_state.x, last_state.y, last_state.w, last_state.h);

	if (!active) {
		if (!style.color.empty()) std::cout << style.color;
		if (!style.background_color.empty()) std::cout << style.background_color;
	}
	else {
		if (!style.color_active.empty()) std::cout << style.color_active;
		if (!style.background_color_active.empty()) std::cout << style.background_color_active;
	}
	if (style.bold) std::cout << ansi::BOLD;
	if (style.underline) std::cout << ansi::UNDERLINE;
	if (style.italic) std::cout << ansi::ITALIC;

	for (int i = 0; i < h; ++i) {
		ansi::move_cursor(y + i, x);
		std::cout << std::string(w, ' ');
	}

	int current_y = y;
	int text_pos = 0;
	while (text_pos < current_label.length() && (current_y - y) < h) {
		ansi::move_cursor(current_y, x);
		int chars_on_line = (w < (int)(current_label.length() - text_pos)) ? w : (int)(current_label.length() - text_pos);
		std::cout << current_label.substr(text_pos, chars_on_line);
		text_pos += chars_on_line;
		current_y++;
	}
	std::cout << ansi::RESET;
	last_state = { x, y, w, h, current_label, current_active };
}