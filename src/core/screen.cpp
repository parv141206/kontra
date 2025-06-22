#include "core/screen.hpp"
#include "core/ansi.hpp"
#ifdef _WIN32
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#endif
void Screen::render(int x, int y, int w, int h) const {
#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);
#endif

	ansi::clear_screen();
	std::cout << "\033[2J\033[H";

	auto [termWidth, termHeight] = ansi::get_terminal_size();


	int absWidth = (w * termWidth) / 100;
	int absHeight = (h * termHeight) / 100;

	for (const auto& child : children) {
		child->render(x, y, absWidth, absHeight);
	}

	//ansi::move_down(2);
	//ansi::move_cursor(absWidth, absHeight);
}