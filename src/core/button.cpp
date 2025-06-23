#include <iostream>
#include "core/button.hpp"
#include "core/ansi.hpp"

void Button::set_active(bool is_active) {
	active = is_active;
}

bool Button::is_active() const {
	return active;
}

void Button::click() {
	if (on_click_callback) on_click_callback();
}

// Is same as Text component, just with active state handling
void Button::render(int x, int y, int w, int h) const
{
	std::string text_value = label();
	if (w <= 0 || h <= 0 || text_value.empty()) {
		return;
	}

	// Dirty logic
	static bool last_active = false;
	static std::string last_label;
	bool state_changed = (text_value != last_label) || (active != last_active);

	if (!state_changed && !is_dirty()) {
		return;
	}
	if (state_changed) {
		mark_dirty();
	}
	last_label = text_value;
	last_active = active;

	// styles
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
}
