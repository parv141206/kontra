#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>

// This function sets the console to a "raw-like" mode and enables virtual terminal processing
// for ANSI escape codes, which is what we need for mouse events.
void setup_console(DWORD& original_mode) {
    HANDLE h_in = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE h_out = GetStdHandle(STD_OUTPUT_HANDLE);

    if (h_in == INVALID_HANDLE_VALUE || h_out == INVALID_HANDLE_VALUE) {
        std::cerr << "Error: Could not get console handles." << std::endl;
        exit(1);
    }

    GetConsoleMode(h_in, &original_mode);

    DWORD new_mode = original_mode;
    new_mode |= ENABLE_VIRTUAL_TERMINAL_INPUT; // Crucial for receiving ANSI codes from the terminal
    new_mode &= ~ENABLE_PROCESSED_INPUT;      // Pass through Ctrl+C, etc.

    if (!SetConsoleMode(h_in, new_mode)) {
        std::cerr << "Error: Could not set console input mode." << std::endl;
    }

    DWORD original_out_mode = 0;
    GetConsoleMode(h_out, &original_out_mode);
    DWORD new_out_mode = original_out_mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN;
    if (!SetConsoleMode(h_out, new_out_mode)) {
        std::cerr << "Error: Could not set console output mode." << std::endl;
    }
}

void restore_console(DWORD original_mode) {
    SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), original_mode);
}

int main() {
    DWORD original_mode = 0;
    setup_console(original_mode);

    // Tell the terminal we want to receive mouse events (SGR format)
    std::cout << "\033[?1003h\033[?1006h" << std::flush;

    std::cout << "--- Input Test Started ---" << std::endl;
    std::cout << "Scroll your mouse wheel up and down." << std::endl;
    std::cout << "Press regular keys (e.g., a, b, c)." << std::endl;
    std::cout << "Press Ctrl+C to exit." << std::endl;
    std::cout << "--------------------------" << std::endl;

    while (true) {
        if (_kbhit()) {
            int ch = _getch();
            // Print the integer value of the character and the character itself if printable
            std::cout << "Received char: " << ch;
            if (isprint(ch)) {
                std::cout << " ('" << (char)ch << "')";
            }
            std::cout << std::endl;
        }
    }

    // The program will be terminated by Ctrl+C, but this is here for completeness.
    restore_console(original_mode);
    return 0;
}