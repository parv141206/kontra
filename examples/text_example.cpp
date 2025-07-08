// ===================================================================
// KONTRA TUI: text_example.cpp
//
// This example demonstrates the `Text` component, the most fundamental
// building block for displaying information in your TUI.
//
// It covers:
// - Creating simple, static text.
// - Creating dynamic, "reactive" text that updates automatically.
// - Using the `StyleBuilder` to create complex visual styles.
// ===================================================================

#include "../include/kontra.hpp"
#include <memory>
#include <chrono> // For getting the current time
#include <ctime>  // For formatting the time

int main() {
    // --- 1. Create a Static Text Component ---
    // This is the simplest way to use `Text`. You pass a string literal
    // directly to its constructor. It will never change.
    auto static_text = std::make_shared<Text>("This is a static text component.");

    // --- 2. Create Styled Static Text with StyleBuilder ---
    // The `StyleBuilder` provides a clean, fluent interface for creating
    // custom styles. You chain `set_...()` methods and finish with `build()`.
    auto styled_text_style = StyleBuilder()
        .set_color(ansi::FG_CYAN)
        .set_background_color(ansi::BG_BRIGHT_BLACK)
        .set_bold(true)
        .set_italic(true)
        .build();
    
    auto styled_text = std::make_shared<Text>(
        "This text is styled using the StyleBuilder.",
        styled_text_style
    );

    // --- 3. Create a Dynamic (Reactive) Text Component ---
    // This is a powerful feature of Kontra TUI. Instead of a string,
    // we pass a C++ lambda function `[](){ ... }` to the constructor.
    // On every single render, the library will re-execute this lambda
    // and display its return value. This makes creating things like
    // clocks or counters incredibly easy.

    auto dynamic_text = std::make_shared<Text>(
        // This lambda gets the current time and formats it as a string.
        []() {
            auto now = std::chrono::system_clock::now();
            auto time_t_now = std::chrono::system_clock::to_time_t(now);
            char time_str[100];
            // Use `localtime_s` on Windows or `localtime_r` on Linux for thread safety
            #ifdef _WIN32
                tm local_tm;
                localtime_s(&local_tm, &time_t_now);
                strftime(time_str, sizeof(time_str), "%H:%M:%S", &local_tm);
            #else
                tm local_tm;
                localtime_r(&time_t_now, &local_tm);
                strftime(time_str, sizeof(time_str), "%H:%M:%S", &local_tm);
            #endif
            return "Reactive Time: " + std::string(time_str);
        },
        TextStyle(ansi::FG_GREEN) // We can style dynamic text too!
    );

    // --- 4. Layout ---
    // We use a `List` component to stack our different text examples vertically.
    auto layout = std::make_shared<List>(
        static_text,
        styled_text,
        dynamic_text
    );
    layout->set_gap(2); // Add some space between them

    // Wrap the whole thing in a border for a nice presentation.
    auto bordered_layout = std::make_shared<Border>(
        layout,
        BorderStyleBuilder().set_title("Text Component Showcase").build()
    );
    bordered_layout->set_padding(1);

    // --- 5. Screen and Run ---
    auto screen = std::make_shared<Screen>(bordered_layout);

    kontra::run(screen, [&](const InputEvent& event) {
        // Static example, no input needed.
        });

    return 0;
}
