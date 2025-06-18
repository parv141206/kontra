/*****************************************************************//**
 * \file   ansi.hpp
 * \brief  This file contains ANSI escape codes for terminal control. It also contains few functions to manipulate cursor position and screen.
 *
 * \author parv141206
 * \date   June 2025
 *********************************************************************/
#pragma once
#include <string>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

namespace ansi {

	// Box drawing characters
	constexpr bool useAsciiBox = true;
	const char tl = useAsciiBox ? '+' : '┌';
	const char tr = useAsciiBox ? '+' : '┐';
	const char bl = useAsciiBox ? '+' : '└';
	const char br = useAsciiBox ? '+' : '┘';
	const char h = useAsciiBox ? '-' : '─';
	const char v = useAsciiBox ? '|' : '│';



	// Cursor movement
	inline constexpr const char* CLEAR_SCREEN = "\033[2J";
	inline constexpr const char* CURSOR_HOME = "\033[H";
	inline constexpr const char* SAVE_CURSOR = "\033[s";
	inline constexpr const char* RESTORE_CURSOR = "\033[u";
	inline constexpr const char* HIDE_CURSOR = "\033[?25l";
	inline constexpr const char* SHOW_CURSOR = "\033[?25h";

	// Screen clearing
	inline constexpr const char* CLEAR_TO_END = "\033[J";
	inline constexpr const char* CLEAR_TO_START = "\033[1J";
	inline constexpr const char* CLEAR_LINE = "\033[K";
	inline constexpr const char* CLEAR_LINE_TO_START = "\033[1K";
	inline constexpr const char* CLEAR_ENTIRE_LINE = "\033[2K";

	// Text styles
	inline constexpr const char* RESET = "\033[0m";
	inline constexpr const char* BOLD = "\033[1m";
	inline constexpr const char* DIM = "\033[2m";
	inline constexpr const char* ITALIC = "\033[3m";
	inline constexpr const char* UNDERLINE = "\033[4m";
	inline constexpr const char* INVERSE = "\033[7m";
	inline constexpr const char* STRIKETHROUGH = "\033[9m";

	// Foreground colors
	inline constexpr const char* FG_BLACK = "\033[30m";
	inline constexpr const char* FG_RED = "\033[31m";
	inline constexpr const char* FG_GREEN = "\033[32m";
	inline constexpr const char* FG_YELLOW = "\033[33m";
	inline constexpr const char* FG_BLUE = "\033[34m";
	inline constexpr const char* FG_MAGENTA = "\033[35m";
	inline constexpr const char* FG_CYAN = "\033[36m";
	inline constexpr const char* FG_WHITE = "\033[37m";

	inline constexpr const char* FG_BRIGHT_BLACK = "\033[90m";
	inline constexpr const char* FG_BRIGHT_RED = "\033[91m";
	inline constexpr const char* FG_BRIGHT_GREEN = "\033[92m";
	inline constexpr const char* FG_BRIGHT_YELLOW = "\033[93m";
	inline constexpr const char* FG_BRIGHT_BLUE = "\033[94m";
	inline constexpr const char* FG_BRIGHT_MAGENTA = "\033[95m";
	inline constexpr const char* FG_BRIGHT_CYAN = "\033[96m";
	inline constexpr const char* FG_BRIGHT_WHITE = "\033[97m";

	inline constexpr const char* FG_DEFAULT = "\033[39m";

	// Background colors
	inline constexpr const char* BG_BLACK = "\033[40m";
	inline constexpr const char* BG_RED = "\033[41m";
	inline constexpr const char* BG_GREEN = "\033[42m";
	inline constexpr const char* BG_YELLOW = "\033[43m";
	inline constexpr const char* BG_BLUE = "\033[44m";
	inline constexpr const char* BG_MAGENTA = "\033[45m";
	inline constexpr const char* BG_CYAN = "\033[46m";
	inline constexpr const char* BG_WHITE = "\033[47m";

	inline constexpr const char* BG_BRIGHT_BLACK = "\033[100m";
	inline constexpr const char* BG_BRIGHT_RED = "\033[101m";
	inline constexpr const char* BG_BRIGHT_GREEN = "\033[102m";
	inline constexpr const char* BG_BRIGHT_YELLOW = "\033[103m";
	inline constexpr const char* BG_BRIGHT_BLUE = "\033[104m";
	inline constexpr const char* BG_BRIGHT_MAGENTA = "\033[105m";
	inline constexpr const char* BG_BRIGHT_CYAN = "\033[106m";
	inline constexpr const char* BG_BRIGHT_WHITE = "\033[107m";

	inline constexpr const char* BG_DEFAULT = "\033[49m";


	// Cursor movement utils
	inline void move_cursor(int row, int col) {
		std::cout << "\033[" << row << ";" << col << "H";
	}

	inline void move_up(int n = 1) {
		std::cout << "\033[" << n << "A";
	}

	inline void move_down(int n = 1) {
		std::cout << "\033[" << n << "B";
	}

	inline void move_right(int n = 1) {
		std::cout << "\033[" << n << "C";
	}

	inline void move_left(int n = 1) {
		std::cout << "\033[" << n << "D";
	}

	inline void clear_screen() {
		std::cout << CLEAR_SCREEN << CURSOR_HOME;
	}

	inline void clear_line() {
		std::cout << CLEAR_ENTIRE_LINE;
	}

	inline void hide_cursor() {
		std::cout << HIDE_CURSOR;
	}

	inline void show_cursor() {
		std::cout << SHOW_CURSOR;
	}

	inline void save_cursor() {
		std::cout << SAVE_CURSOR;
	}

	inline void restore_cursor() {
		std::cout << RESTORE_CURSOR;
	}

	// Completely yoinked from the internet, who writes dis shit
	inline std::pair<int, int> get_terminal_size() {
#ifdef _WIN32
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
		return { width, height };
#else
		struct winsize w;
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		return { w.ws_col, w.ws_row };
#endif
	}
}
