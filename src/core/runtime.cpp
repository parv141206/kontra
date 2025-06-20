/**
 *
 * WARNING
 *
 * The code below is heavily vibe coded. (hindi lang) chale to chand tak nahi to raat tak
 *
 * Before scrolling, be mentally prepared.
 *
 * Hail to the makers of these functions and syntaxes, i'd die writing these.
 *
 */
#include "core/runtime.hpp"
#include "core/ansi.hpp"

#include <iostream>
#include <thread>
#include <chrono>

// VIBE CODE STARTS HERE

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
void clearScreen() {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hOut == INVALID_HANDLE_VALUE) return;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hOut, &csbi);
	SMALL_RECT windowSize = csbi.srWindow;
	COORD newSize;
	newSize.X = windowSize.Right - windowSize.Left + 1;
	newSize.Y = windowSize.Bottom - windowSize.Top + 1;
	SetConsoleScreenBufferSize(hOut, newSize);
	DWORD cells = newSize.X * newSize.Y;
	COORD topLeft = { 0, 0 };
	DWORD written;
	FillConsoleOutputCharacter(hOut, ' ', cells, topLeft, &written);
	FillConsoleOutputAttribute(hOut, csbi.wAttributes, cells, topLeft, &written);
	SetConsoleCursorPosition(hOut, topLeft);
}
void hideCursor() {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hOut, &cursorInfo);
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hOut, &cursorInfo);
}
#else
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>
#include <termios.h>

void clearScreen() {
	std::cout << "\033[2J\033[H";
}
void hideCursor() {
	std::cout << "\033[?25l";
}

bool kbhit() {
	fd_set set;
	struct timeval timeout;
	FD_ZERO(&set);
	FD_SET(STDIN_FILENO, &set);
	timeout.tv_sec = 0;
	timeout.tv_usec = 0;
	return select(STDIN_FILENO + 1, &set, nullptr, nullptr, &timeout) > 0;
}

char getch() {
	struct termios oldt, newt;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	char ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return ch;
}
#endif

// VIBE CODE ENDS HERE

namespace kontra {

	void init() {
		hideCursor();
	}

	void shutdown() {
		std::cout << ansi::RESET << "\033[?25h"; 
	}

	void run(std::shared_ptr<Screen> screen, std::function<void(char)> onInput) {
		init();
		bool dirty = true;
		try {
			while (true) {
#ifdef _WIN32
				if (_kbhit()) {
					char ch = _getch();
					if (onInput) onInput(ch);
					dirty = true;
				}
#else
				if (kbhit()) {
					char ch = getch();
					if (onInput) onInput(ch);
					dirty = true;
				}
#endif


				if (dirty) {
					clearScreen();
					screen->render(1, 1, 100, 95);
					dirty = false;
				}
				std::this_thread::sleep_for(std::chrono::milliseconds(16));
			}
		}
		catch (const std::exception& e) {
			std::cerr << ansi::BG_RED << ansi::FG_BLACK << "\n[Runtime Error] " << e.what() << '\n' << ansi::RESET;
		}
		shutdown();
	}

}
