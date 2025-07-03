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
#include <sys/ioctl.h>
#include <sys/select.h>
#endif

namespace kontra::terminal
{

    void handle_signal(int signal_num)
    {
        if (signal_num == SIGINT)
        {
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

    void initialize()
    {
        signal(SIGINT, handle_signal);

        HANDLE h_in = GetStdHandle(STD_INPUT_HANDLE);
        HANDLE h_out = GetStdHandle(STD_OUTPUT_HANDLE);

        GetConsoleMode(h_in, &original_in_mode);
        GetConsoleMode(h_out, &original_out_mode);

        DWORD new_in_mode = ENABLE_VIRTUAL_TERMINAL_INPUT;
        DWORD new_out_mode = ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN;

        SetConsoleMode(h_in, new_in_mode);
        SetConsoleMode(h_out, new_out_mode);

        ansi::hide_cursor();
        std::cout << "\033[?1003h\033[?1006h" << std::flush;
    }

    void shutdown()
    {
        std::cout << "\033[?1003l\033[?1006l" << std::flush;
        ansi::show_cursor();

        SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), original_in_mode);
        SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), original_out_mode);
    }

    void read_input_events(std::vector<InputEvent> &events)
    {
        std::string buffer;
        while (_kbhit())
        {
            buffer += _getch();
        }
        if (buffer.empty())
            return;
        size_t pos = 0;
        while (pos < buffer.length())
        {
            if (buffer[pos] == '\033' && pos + 2 < buffer.length() && buffer[pos + 1] == '[' && buffer[pos + 2] == '<')
            {
                size_t end_m = buffer.find('M', pos + 3);
                if (end_m != std::string::npos)
                {
                    std::string sequence = buffer.substr(pos + 3, end_m - (pos + 3));
                    int btn, x, y;
                    if (sscanf(sequence.c_str(), "%d;%d;%d", &btn, &x, &y) == 3)
                    {
                        if (btn == 0)
                            events.push_back({EventType::MOUSE_PRESS, 0, x, y});
                        if (btn == 64)
                            events.push_back({EventType::MOUSE_SCROLL_UP, 0, x, y});
                        if (btn == 65)
                            events.push_back({EventType::MOUSE_SCROLL_DOWN, 0, x, y});
                    }
                    pos = end_m + 1;
                    continue;
                }
            }
            events.push_back({EventType::KEY_PRESS, buffer[pos]});
            pos++;
        }
    }

#else
    // =================================================
    // ---           LINUX IMPLEMENTATION            ---
    // =================================================
    static struct termios orig_termios;

    bool kbhit()
    {
        timeval tv = {0L, 0L};
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds);
        return select(1, &fds, NULL, NULL, &tv) > 0;
    }

    char getch()
    {
        char buf = 0;
        if (read(STDIN_FILENO, &buf, 1) < 0)
        {
            perror("read()");
        }
        return buf;
    }

    void enable_raw_mode()
    {
        tcgetattr(STDIN_FILENO, &orig_termios);
        termios raw = orig_termios;
        raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
        raw.c_oflag &= ~(OPOST);
        raw.c_cflag |= (CS8);
        raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
        raw.c_cc[VMIN] = 0;
        raw.c_cc[VTIME] = 1;
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    }

    void disable_raw_mode()
    {
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
    }

    void initialize()
    {
        signal(SIGINT, handle_signal);
        enable_raw_mode();
        atexit(disable_raw_mode);

        ansi::hide_cursor();
        std::cout << "\033[?1003h\03_3[?1006h" << std::flush;
    }

    void shutdown()
    {
        std::cout << "\033[?1003l\033[?1006l" << std::flush;
        ansi::show_cursor();
        disable_raw_mode();
    }

    void read_input_events(std::vector<InputEvent> &events)
    {
        std::string buffer;
        if (kbhit())
        {
            char c;
            while (read(STDIN_FILENO, &c, 1) == 1)
            {
                buffer += c;
            }
        }
        if (buffer.empty())
            return;
        size_t pos = 0;
        while (pos < buffer.length())
        {
            if (buffer[pos] == '\033' && pos + 2 < buffer.length() && buffer[pos + 1] == '[' && buffer[pos + 2] == '<')
            {
                size_t end_m = buffer.find_first_of("mM", pos + 3);
                if (end_m != std::string::npos)
                {
                    std::string sequence = buffer.substr(pos + 3, end_m - (pos + 3));
                    int btn, x, y;
                    if (sscanf(sequence.c_str(), "%d;%d;%d", &btn, &x, &y) == 3)
                    {
                        if (btn == 0)
                            events.push_back({EventType::MOUSE_PRESS, 0, x, y});
                        if (btn == 64)
                            events.push_back({EventType::MOUSE_SCROLL_UP, 0, x, y});
                        if (btn == 65)
                            events.push_back({EventType::MOUSE_SCROLL_DOWN, 0, x, y});
                    }
                    pos = end_m + 1;
                    continue;
                }
            }
            events.push_back({EventType::KEY_PRESS, buffer[pos]});
            pos++;
        }
    }
#endif

}
