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

namespace kontra::terminal
{
    void handle_signal(int signal_num) {
        if (signal_num == SIGINT) {
            shutdown();
            exit(0);
        }
    }

#ifdef _WIN32
    // =================================================
    // ---           WINDOWS IMPLEMENTATION          ---
    // =================================================
    static DWORD original_in_mode = 0;
    static DWORD original_out_mode = 0;

    void initialize() {
        signal(SIGINT, handle_signal);
        HANDLE h_in = GetStdHandle(STD_INPUT_HANDLE);
        HANDLE h_out = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleMode(h_in, &original_in_mode);
        GetConsoleMode(h_out, &original_out_mode);
        DWORD new_in_mode = ENABLE_VIRTUAL_TERMINAL_INPUT | ENABLE_PROCESSED_INPUT;
        DWORD new_out_mode = ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN;
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

    void read_input_events(std::vector<InputEvent> &events) {
        while (_kbhit()) {
            int c = _getch();

            if (c == 224 || c == 0) { 
                int c2 = _getch();
                switch (c2) {
                    case 72: events.push_back({EventType::KEY_UP}); continue;
                    case 80: events.push_back({EventType::KEY_DOWN}); continue;
                    case 75: events.push_back({EventType::KEY_LEFT}); continue;
                    case 77: events.push_back({EventType::KEY_RIGHT}); continue;
                }
                continue;
            }
            
            switch (c) {
                case 13: events.push_back({EventType::KEY_ENTER}); continue;
                case 8:  events.push_back({EventType::KEY_BACKSPACE}); continue;
                case 27:
                    if (_kbhit()) { 
                        if (_getch() == '[') {
                             if (_kbhit() && _getch() == '<') {
                                std::string buffer;
                                char next_char;
                                while(_kbhit() && (next_char = _getch()) != 'M' && next_char != 'm') {
                                    buffer += next_char;
                                }
                                int btn, x, y;
                                if (sscanf(buffer.c_str(), "%d;%d;%d", &btn, &x, &y) == 3) {
                                     if (btn == 0)  events.push_back({EventType::MOUSE_PRESS, 0, x, y});
                                     if (btn == 64) events.push_back({EventType::MOUSE_SCROLL_UP, 0, x, y});
                                     if (btn == 65) events.push_back({EventType::MOUSE_SCROLL_DOWN, 0, x, y});
                                }
                                continue;
                            }
                        }
                    }
                    events.push_back({EventType::KEY_ESCAPE});
                    continue;
            }
            
            events.push_back({EventType::KEY_PRESS, (char)c});
        }
    }

#else
    // =================================================
    // ---           LINUX IMPLEMENTATION            ---
    // =================================================
    static struct termios orig_termios;

    void disable_raw_mode() {
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
    }

    void enable_raw_mode() {
        tcgetattr(STDIN_FILENO, &orig_termios);
        atexit(disable_raw_mode);
        termios raw = orig_termios;
        raw.c_lflag &= ~(ECHO | ICANON);
        raw.c_cc[VMIN] = 0;
        raw.c_cc[VTIME] = 1; // 100ms timeout
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    }

    void initialize() {
        signal(SIGINT, handle_signal);
        enable_raw_mode();
        ansi::hide_cursor();
        std::cout << "\033[?1003h\033[?1006h" << std::flush;
    }

    void shutdown() {
        std::cout << "\033[?1003l\033[?1006l" << std::flush;
        ansi::show_cursor();
        disable_raw_mode();
    }

    void read_input_events(std::vector<InputEvent> &events) {
        char c_in[64]; 
        int nread = read(STDIN_FILENO, &c_in, sizeof(c_in));

        if (nread <= 0) return;

        std::string buffer(c_in, nread);
        size_t pos = 0;

        while (pos < buffer.length()) {
            char current_char = buffer[pos];

            switch (current_char) {
                case 10: // Enter 
                    events.push_back({EventType::KEY_ENTER});
                    pos++;
                    continue; 
                case 127: // Backspace 
                    events.push_back({EventType::KEY_BACKSPACE});
                    pos++;
                    continue;
                case 27: 
                    if (pos + 1 < buffer.length() && buffer[pos + 1] == '[') {
                        // Arrow Keys: \033[A, \033[B, \033[C, \033[D
                        if (pos + 2 < buffer.length() && buffer[pos + 2] >= 'A' && buffer[pos + 2] <= 'D') {
                            switch (buffer[pos + 2]) {
                                case 'A': events.push_back({EventType::KEY_UP}); break;
                                case 'B': events.push_back({EventType::KEY_DOWN}); break;
                                case 'C': events.push_back({EventType::KEY_RIGHT}); break;
                                case 'D': events.push_back({EventType::KEY_LEFT}); break;
                            }
                            pos += 3;
                            continue;
                        }
                        // SGR Mouse Event
                        if (pos + 2 < buffer.length() && buffer[pos + 2] == '<') {
                            size_t end_m = buffer.find_first_of("mM", pos + 3);
                            if (end_m != std::string::npos) {
                                std::string sequence = buffer.substr(pos + 3, end_m - (pos + 3));
                                int btn, x, y;
                                if (sscanf(sequence.c_str(), "%d;%d;%d", &btn, &x, &y) == 3) {
                                    if (btn == 0)  events.push_back({ EventType::MOUSE_PRESS, 0, x, y });
                                    if (btn == 64) events.push_back({ EventType::MOUSE_SCROLL_UP, 0, x, y });
                                    if (btn == 65) events.push_back({ EventType::MOUSE_SCROLL_DOWN, 0, x, y });
                                }
                                pos = end_m + 1; 
                                continue;
                            }
                        }
                    }
                    events.push_back({EventType::KEY_ESCAPE});
                    pos++;
                    continue;
            }

            events.push_back({EventType::KEY_PRESS, current_char});
            pos++;
        }
    }
#endif
}
