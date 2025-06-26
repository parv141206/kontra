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
void InputBox::render(ScreenBuffer& buffer, int x, int y, int w, int h) const {
	const std::string border_style = ansi::RESET;
	const std::string text_style = ansi::RESET;
	const std::string cursor_style = ansi::INVERSE;

	const int innerW = w - 2;
	int scroll_offset = 0;
	if (innerW > 0 && !wrap) {
		if (cursor >= innerW) {
			scroll_offset = cursor - innerW + 1;
		}
	}

	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j) {
			const int current_x = x + j;
			const int current_y = y + i;

			const bool is_top = (i == 0);
			const bool is_bottom = (i == h - 1);
			const bool is_left = (j == 0);
			const bool is_right = (j == w - 1);

			if (is_top && is_left) { buffer.set_cell(current_x, current_y, ansi::tl, border_style); continue; }
			if (is_top && is_right) { buffer.set_cell(current_x, current_y, ansi::tr, border_style); continue; }
			if (is_bottom && is_left) { buffer.set_cell(current_x, current_y, ansi::bl, border_style); continue; }
			if (is_bottom && is_right) { buffer.set_cell(current_x, current_y, ansi::br, border_style); continue; }
			if (is_top || is_bottom) { buffer.set_cell(current_x, current_y, ansi::h, border_style); continue; }
			if (is_left || is_right) { buffer.set_cell(current_x, current_y, ansi::v, border_style); continue; }

			const int content_col = j - 1;
			wchar_t char_to_draw = L' ';
			std::string style_to_use = text_style;

			if (scroll_offset + content_col < text.length()) {
				char_to_draw = text[scroll_offset + content_col];
			}

			const int cursor_in_view_col = cursor - scroll_offset;
			if (active && content_col == cursor_in_view_col) {
				style_to_use = cursor_style;
			}

			buffer.set_cell(current_x, current_y, std::string(1, char_to_draw), style_to_use);
		}
	}
}