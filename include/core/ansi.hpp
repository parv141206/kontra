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

namespace ansi {

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
	inline constexpr const char* FG_RED = "\033[31m";
	inline constexpr const char* FG_GREEN = "\033[32m";
	inline constexpr const char* FG_BLUE = "\033[34m";
	inline constexpr const char* FG_DEFAULT = "\033[39m";

	// Background colors
	inline constexpr const char* BG_RED = "\033[41m";
	inline constexpr const char* BG_GREEN = "\033[42m";
	inline constexpr const char* BG_BLUE = "\033[44m";
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
}
