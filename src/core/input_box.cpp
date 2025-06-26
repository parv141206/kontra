#include "core/input_box.hpp"
#include "core/ansi.hpp"
#include "core/utils.hpp"
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
	if (!wrap) return 3;

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
	return lines + 2;
}

void InputBox::set_active(bool is_active) {
	if (active != is_active) {
		active = is_active;
	}
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
	case '\b': case 127:
		if (cursor > 0) {
			text.erase(cursor - 1, 1);
			cursor--;
		}
		break;
	case 27:
		break;
	case 75:
		if (cursor > 0) cursor--;
		break;
	case 77:
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
	if (last_state.x == x && last_state.y == y && last_state.w == w && last_state.h == h && last_state.text == text && last_state.cursor == cursor && last_state.active == active) {
		return;
	}

	clear_area(last_state.x, last_state.y, last_state.w, last_state.h);

	int innerW = w - 2;
	int innerH = h - 2;

	ansi::move_cursor(y, x);
	std::cout << ansi::tl << repeat(ansi::h, innerW) << ansi::tr;

	for (int row = 0; row < innerH; ++row) {
		ansi::move_cursor(y + 1 + row, x);
		std::cout << ansi::v;
		std::string line(innerW, ' ');
		if (wrap) {
			int start = row * innerW;
			if (start < (int)text.size()) {
				std::string slice = text.substr(start, innerW);
				line.replace(0, slice.size(), slice);
			}
		}
		else {
			if (row == 0) {
				int offset = std::max(0, cursor - innerW + 1);
				std::string visible = text.substr(offset, innerW);
				line.replace(0, visible.size(), visible);
			}
		}

		std::cout << line << ansi::v;

		if (active) {
			int display_cursor_pos = cursor - (wrap ? 0 : std::max(0, cursor - innerW + 1));
			int cur_row = wrap ? (display_cursor_pos / innerW) : 0;
			int cur_col = wrap ? (display_cursor_pos % innerW) : display_cursor_pos;

			if (row == cur_row && cur_col < innerW) {
				ansi::save_cursor();
				ansi::move_cursor(y + 1 + cur_row, x + 1 + cur_col);
				char char_under_cursor = (cur_col < (int)line.length()) ? line[cur_col] : ' ';
				std::cout << "\033[7m" << char_under_cursor << "\033[0m"; // Inverse video
				ansi::restore_cursor();
			}
		}
	}

	ansi::move_cursor(y + h - 1, x);
	std::cout << ansi::bl << repeat(ansi::h, innerW) << ansi::br;
	last_state = { x, y, w, h, text, cursor, active };
}