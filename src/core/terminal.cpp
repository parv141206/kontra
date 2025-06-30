/*****************************************************************//**
 * \file   terminal.cpp
 * \brief  Warning, the following code is 80% vibe coded. It may break at any time!
 * 
 * \author parv141206
 * \date   June 2025
 *********************************************************************/
#include "core/terminal.hpp"
#include "core/ansi.hpp"
#include <iostream>
#include <string>
#include <csignal> 
#include <cstdlib> 
#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else
#include <unistd.h>
#include <termios.h>
#endif

namespace kontra::terminal {
    void handle_signal(int signal_num) {
        if (signal_num == SIGINT) {
            shutdown();
            exit(0);
        }
    }
#ifdef _WIN32
    static DWORD original_in_mode = 0;
    static DWORD original_out_mode = 0;

    void initialize() {
        signal(SIGINT, handle_signal);
        HANDLE h_in = GetStdHandle(STD_INPUT_HANDLE);
        HANDLE h_out = GetStdHandle(STD_OUTPUT_HANDLE);

        if (h_in == INVALID_HANDLE_VALUE || h_out == INVALID_HANDLE_VALUE) {
            return;
        }

        GetConsoleMode(h_in, &original_in_mode);
        GetConsoleMode(h_out, &original_out_mode);

        DWORD new_in_mode = original_in_mode | ENABLE_VIRTUAL_TERMINAL_INPUT | ENABLE_MOUSE_INPUT;

        new_in_mode &= ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);

        DWORD new_out_mode = original_out_mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN;

        SetConsoleMode(h_in, new_in_mode);
        SetConsoleMode(h_out, new_out_mode);

        ansi::hide_cursor();
        std::cout << "\033[?1003h\033[?1006h" << std::flush;
    }

    void shutdown() {
        std::cout << "\033[?1003l\033[?1006l" << std::flush;
        ansi::show_cursor();

        SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), original_in_mode);
        SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), original_out_mode);
    }

    void read_input_events(std::vector<InputEvent>& events) {
        std::string buffer;
        while (_kbhit()) {
            buffer += _getch();
        }

        if (buffer.empty()) return;

        size_t pos = 0;
        while (pos < buffer.length()) {
            if (buffer[pos] == '\033' && pos + 2 < buffer.length() && buffer[pos + 1] == '[' && buffer[pos + 2] == '<') {
                size_t end_m = buffer.find_first_of("mM", pos + 3);
                if (end_m != std::string::npos) {
                    std::string sequence = buffer.substr(pos + 3, end_m - (pos + 3));
                    int btn, x, y;
                    if (sscanf(sequence.c_str(), "%d;%d;%d", &btn, &x, &y) == 3) {
                        if (btn == 0 && buffer[end_m] == 'M')  events.push_back({ EventType::MOUSE_PRESS, 0, x, y }); 
                        if (btn == 64) events.push_back({ EventType::MOUSE_SCROLL_UP, 0, x, y });
                        if (btn == 65) events.push_back({ EventType::MOUSE_SCROLL_DOWN, 0, x, y });
                    }
                    pos = end_m + 1; 
                    continue;
                }
            }

            events.push_back({ EventType::KEY_PRESS, buffer[pos] });
            pos++;
        }
    }

#else
    // FUCK LINUX AND MAC FOR NOW 
    void initialize() { /* ... */ }
    void shutdown() { /* ... */ }
    void read_input_events(std::vector<InputEvent>& events) { /* ... */ }
#endif

}