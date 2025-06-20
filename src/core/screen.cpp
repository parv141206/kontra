#include "core/screen.hpp"
#include "core/ansi.hpp"

void Screen::render(int x, int y, int w, int h) const {
	ansi::clear_screen();
	std::cout << "\033[2J\033[H";

	auto [termWidth, termHeight] = ansi::get_terminal_size();


	int absWidth = (w * termWidth) / 100;
	int absHeight = (h * termHeight) / 100;

	for (const auto& child : children) {
		child->render(x, y, absWidth, absHeight);
	}

	ansi::move_down(2);
	//ansi::move_cursor(absWidth, absHeight);
}