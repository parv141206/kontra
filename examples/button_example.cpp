// ===================================================================
// KONTRA TUI: button_example.cpp
//
// Demonstrates interactive `Button` components with keyboard and mouse.
// ===================================================================
#include "../include/kontra.hpp"
#include <vector>

int main() {
    std::string message = "Use Tab/Enter or Click a button!";
    auto display_text = std::make_shared<Text>([&]() { return message; });

    auto button1 = std::make_shared<Button>(
        "Set Message 1",
        [&]() { message = "Button 1 was clicked!"; },
        ButtonStyleBuilder().set_bold(true).set_background_color(ansi::BG_DEFAULT).set_background_color_active(ansi::BG_BLUE).build()
    );
    auto button2 = std::make_shared<Button>(
        "Set Message 2",
        [&]() { message = "Button 2 was clicked!"; },
        ButtonStyleBuilder().set_bold(true).set_background_color(ansi::BG_BLACK).set_background_color_active(ansi::BG_BLUE).build()
    );

    button1->set_active(true);
    std::shared_ptr<Button> active_button = button1;

    // Store buttons for easy iteration during mouse clicks
    std::vector<std::shared_ptr<Button>> buttons = { button1, button2 };

    auto layout = std::make_shared<List>(display_text, button1, button2);
    layout->set_gap(1);
    auto screen = std::make_shared<Screen>(std::make_shared<Border>(layout));

    // UPDATED: The event loop now handles keyboard and mouse events.
    kontra::run(screen, [&](const InputEvent& event) {

        if (event.type == EventType::KEY_PRESS) {
            if (event.key == '\t') { // Tab key
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
            else if (event.key == '\n' || event.key == '\r') { // Enter key
                active_button->click();
            }
        }
        else if (event.type == EventType::MOUSE_PRESS) {
            for (const auto& btn : buttons) {
                if (btn->contains(event.mouse_x, event.mouse_y)) {
                    btn->click();
                    // Optional: update the active button on click
                    active_button->set_active(false);
                    btn->set_active(true);
                    active_button = btn;
                    break;
                }
            }
        }
        });

    return 0;
}