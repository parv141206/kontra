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
#include "core/screen_buffer.hpp"
#include "core/event.hpp"
#include "core/terminal.hpp"
#include <iostream>
#include <thread>
#include <chrono>

// VIBE CODE STARTS HERE

#ifdef _WIN32
#include <windows.h>
#include <conio.h>

void clearScreen()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
        return;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hOut, &csbi);
    SMALL_RECT windowSize = csbi.srWindow;
    COORD newSize;
    newSize.X = windowSize.Right - windowSize.Left + 1;
    newSize.Y = windowSize.Bottom - windowSize.Top + 1;
    SetConsoleScreenBufferSize(hOut, newSize);
    DWORD cells = newSize.X * newSize.Y;
    COORD topLeft = {0, 0};
    DWORD written;
    FillConsoleOutputCharacter(hOut, ' ', cells, topLeft, &written);
    FillConsoleOutputAttribute(hOut, csbi.wAttributes, cells, topLeft, &written);
    SetConsoleCursorPosition(hOut, topLeft);
}

void hideCursor()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hOut, &cursorInfo);
}

void showCursor()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(hOut, &cursorInfo);
}

#else 
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>

static struct termios orig_termios;

void disableRawMode()
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
    std::cout << ansi::RESET << ansi::SHOW_CURSOR << std::flush;
}

void enableRawMode()
{
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    raw.c_iflag &= ~(IXON | ICRNL);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void clearScreen()
{
    std::cout << "\033[2J\033[H";
}

void hideCursor()
{
    std::cout << "\033[?25l";
}

void showCursor()
{
    std::cout << "\033[?25h";
}

bool kbhit()
{
    fd_set set;
    struct timeval timeout{};
    FD_ZERO(&set);
    FD_SET(STDIN_FILENO, &set);
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;
    return select(STDIN_FILENO + 1, &set, nullptr, nullptr, &timeout) > 0;
}

char getch()
{
    char ch = 0;
    read(STDIN_FILENO, &ch, 1);
    return ch;
}
#endif

// VIBE CODE ENDS HERE

namespace kontra
{

    void init()
    {
#ifdef _WIN32
        HANDLE h_in = GetStdHandle(STD_INPUT_HANDLE);
        HANDLE h_out = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD in_mode = 0, out_mode = 0;
        GetConsoleMode(h_in, &in_mode);
        GetConsoleMode(h_out, &out_mode);
        in_mode |= ENABLE_VIRTUAL_TERMINAL_INPUT;
        in_mode &= ~ENABLE_ECHO_INPUT;
        in_mode &= ~ENABLE_LINE_INPUT;
        SetConsoleMode(h_in, in_mode);
        out_mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(h_out, out_mode);
#endif
        hideCursor();
        std::cout << "\033[?1003h\033[?1006h" << std::flush;
    }

    void shutdown()
    {
        std::cout << "\033[?1003l\033[?1006l" << std::flush;
        showCursor();
    }

    void run(std::shared_ptr<Screen> screen, std::function<void(const InputEvent &)> onInput)
    {
        terminal::initialize();

        auto [w, h] = ansi::get_terminal_size();
        ScreenBuffer current_buffer(w, h);
        ScreenBuffer previous_buffer(w, h);
        std::cout << ansi::CLEAR_SCREEN << std::flush;

        std::vector<InputEvent> events;

        while (true)
        {
            events.clear();
            terminal::read_input_events(events);

            for (const auto &event : events)
            {
                if (event.type == EventType::KEY_PRESS && event.key == 17)
                {
                    terminal::shutdown();
                    return;
                }
                if (onInput)
                {
                    onInput(event);
                }
            }

            auto [term_w, term_h] = ansi::get_terminal_size();
            if (term_w != current_buffer.width() || term_h != current_buffer.height())
            {
                current_buffer.resize(term_w, term_h);
                previous_buffer.resize(term_w, term_h);
                std::cout << ansi::CLEAR_SCREEN;
            }
            current_buffer.clear();
            screen->render(current_buffer, 0, 0, current_buffer.width(), current_buffer.height());
            std::string out_str;
            std::string last_style = " ";
            for (int y_idx = 0; y_idx < current_buffer.height(); ++y_idx)
            {
                for (int x_idx = 0; x_idx < current_buffer.width(); ++x_idx)
                {
                    if (current_buffer.get_cell(x_idx, y_idx) != previous_buffer.get_cell(x_idx, y_idx))
                    {
                        out_str += "\033[" + std::to_string(y_idx + 1) + ";" + std::to_string(x_idx + 1) + "H";
                        const auto &cell = current_buffer.get_cell(x_idx, y_idx);
                        if (cell.style != last_style)
                        {
                            out_str += cell.style;
                            last_style = cell.style;
                        }
                        out_str += cell.character;
                    }
                }
            }
            out_str += ansi::RESET;
            out_str += ansi::HIDE_CURSOR;
            std::cout << out_str << std::flush;
            previous_buffer = current_buffer;

            std::this_thread::sleep_for(std::chrono::milliseconds(16));
        }
    }
}
