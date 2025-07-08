// ===================================================================
// KONTRA TUI: button_example.cpp
//
// Demonstrates interactive `Button` components with keyboard and mouse.
// ===================================================================
#include "../include/kontra.hpp"
#include <vector>
#include <memory>

int main() {
    std::string message = "Use Tab/Enter or Click a button!";
    auto display_text = std::make_shared<Text>([&]() { return message; });

    // --- Create a style for the first button ---
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

    // --- Create a style for the second button ---
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

    // --- Focus Management ---
    button1->set_active(true);
    std::shared_ptr<Button> active_button = button1;
    std::vector<std::shared_ptr<Button>> buttons = { button1, button2 };

    // --- Layout ---
    auto layout = std::make_shared<List>(display_text, button1, button2);
    layout->set_gap(1);
    auto screen = std::make_shared<Screen>(std::make_shared<Border>(layout));

    // --- Event Loop ---
    kontra::run(screen, [&](const InputEvent& event) {
        switch (event.type) {
            case EventType::KEY_PRESS:
                if (event.key == '\t') {
                    active_button->set_active(false);
                    if (active_button == button1) {
                        active_button = button2;
                    } else {
                        active_button = button1;
                    }
                    active_button->set_active(true);
                }
                break;

            case EventType::KEY_ENTER:
                active_button->click();
                break;

            case EventType::MOUSE_PRESS:
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
