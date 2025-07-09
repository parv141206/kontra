// ===================================================================
// KONTRA TUI Example: button_example.cpp
//
// This example demonstrates interactive `Button` components that respond
// to both keyboard and mouse input. Buttons are styled using the
// `ButtonStyleBuilder`, and the focused button can be toggled with Tab.
// ===================================================================

#include "../include/kontra.hpp"
#include <vector>
#include <memory>

int main() {
    // --- 1. State Variable ---
    // This `message` is updated by button callbacks and shown on screen.
    std::string message = "Use Tab/Enter or Click a button!";
    auto display_text = std::make_shared<Text>([&]() { return message; });

    // --- 2. First Button + Style ---
    // A blue button with white text when inactive, inverts on focus.
    auto button1_style = ButtonStyleBuilder()
        .set_inactive_style(
            StyleBuilder()
                .set_color(ansi::FG_WHITE)
                .set_background_color(ansi::BG_BLUE)
                .set_bold(true)
                .build()
        )
        .set_active_style(
            StyleBuilder()
                .set_color(ansi::FG_BLUE)
                .set_background_color(ansi::BG_BRIGHT_WHITE)
                .set_bold(true)
                .build()
        )
        .build();

    auto button1 = std::make_shared<Button>(
        "Set Message 1",
        [&]() { message = "Button 1 was clicked!"; },
        button1_style
    );

    // --- 3. Second Button + Style ---
    // A red button with white text when inactive, inverts on focus.
    auto button2_style = ButtonStyleBuilder()
        .set_inactive_style(
            StyleBuilder()
                .set_color(ansi::FG_WHITE)
                .set_background_color(ansi::BG_RED)
                .set_bold(true)
                .build()
        )
        .set_active_style(
            StyleBuilder()
                .set_color(ansi::FG_RED)
                .set_background_color(ansi::BG_BRIGHT_WHITE)
                .set_bold(true)
                .build()
        )
        .build();

    auto button2 = std::make_shared<Button>(
        "Set Message 2",
        [&]() { message = "Button 2 was clicked!"; },
        button2_style
    );

    // --- 4. Focus Management ---
    // By default, the first button is focused.
    button1->set_active(true);
    std::shared_ptr<Button> active_button = button1;
    std::vector<std::shared_ptr<Button>> buttons = { button1, button2 };

    // --- 5. Layout ---
    // Stack the message + buttons vertically inside a bordered container.
    auto layout = std::make_shared<List>(display_text, button1, button2);
    layout->set_gap(1);
    auto screen = std::make_shared<Screen>(
        std::make_shared<Border>(layout)
    );

    // --- 6. Event Loop ---
    // Handle keyboard + mouse events to toggle focus and trigger clicks.
    kontra::run(screen, [&](const InputEvent& event) {
        switch (event.type) {
            case EventType::KEY_PRESS:
                if (event.key == '\t') {
                    // Tab switches active button
                    active_button->set_active(false);
                    active_button = (active_button == button1) ? button2 : button1;
                    active_button->set_active(true);
                }
                break;

            case EventType::KEY_ENTER:
                // Pressing Enter triggers click on active button
                active_button->click();
                break;

            case EventType::MOUSE_PRESS:
                // Clicking a button makes it active and triggers click
                for (const auto& btn : buttons) {
                    if (btn->contains(event.mouse_x, event.mouse_y)) {
                        btn->click();
                        active_button->set_active(false);
                        btn->set_active(true);
                        active_button = btn;
                        break;
                    }
                }
                break;

            default:
                break;
        }
    });

    return 0;
}
