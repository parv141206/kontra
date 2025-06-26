// ===================================================================
// KONTRA TUI: button_example.cpp
//
// This example demonstrates how to create interactive `Button` components.
// It covers:
// - Creating buttons with text labels.
// - Assigning a callback function to be executed on `click()`.
// - Using the `ButtonStyleBuilder` for easy styling.
// - Managing an "active" state to control which button is focused.
// - Handling keyboard input to switch focus and trigger clicks.
// ===================================================================

#include "../include/kontra.hpp"
#include "../include/core/utils.hpp" // For the `chain` utility

int main() {
    // --- 1. State Management ---
    // We need a variable to hold the message that our buttons will change.
    std::string message = "Press a button!";

    // --- 2. Component Initialization ---
    // A Text component to display the current message.
    auto display_text = std::make_shared<Text>([&]() { return message; });

    // --- 3. Create the Buttons ---
    // We define a callback lambda for each button. This is the code that
    // runs when the button is "clicked".
    auto button1 = std::make_shared<Button>(
        "Set Message 1",
        [&]() { message = "Button 1 was clicked!"; },
        ButtonStyleBuilder()
        .set_color(ansi::FG_WHITE)
        .set_background_color(ansi::BG_BLUE)
        .set_color_active(ansi::FG_BLUE)
        .set_background_color_active(ansi::BG_BRIGHT_WHITE)
        .set_bold(true)
        .build()
    );

    auto button2 = std::make_shared<Button>(
        "Set Message 2",
        [&]() { message = "Button 2 was clicked!"; },
        ButtonStyleBuilder()
        .set_color(ansi::FG_WHITE)
        .set_background_color(ansi::BG_RED)
        .set_color_active(ansi::FG_RED)
        .set_background_color_active(ansi::BG_BRIGHT_WHITE)
        .set_bold(true)
        .build()
    );

    // --- 4. Focus Management ---
    // We must manually track which button is currently active.
    button1->set_active(true); // Start with the first button active
    button2->set_active(false);
    std::shared_ptr<Button> active_button = button1;

    // --- 5. Layout ---
    auto layout = std::make_shared<List>(
        display_text,
        button1,
        button2
    );
    layout->set_gap(1);

    auto screen = std::make_shared<Screen>(std::make_shared<Border>(layout));

    // --- 6. Event Loop ---
    // We handle Tab to switch focus and Enter to "click" the active button.
    kontra::run(screen, [&](char ch) {
        if (ch == 17) { exit(0); } // Exit on Ctrl+Q

        if (ch == '\t') { // Tab key
            // Toggle active state between the two buttons
            if (active_button == button1) {
                button1->set_active(false);
                button2->set_active(true);
                active_button = button2;
            }
            else {
                button2->set_active(false);
                button1->set_active(true);
                active_button = button1;
            }
        }

        if (ch == '\n' || ch == '\r') { // Enter key
            // Trigger the click callback of whichever button is currently active.
            active_button->click();
        }
        });

    return 0;
}