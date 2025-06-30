// ===================================================================
// KONTRA TUI: mouse_scroll_example.cpp
//
// This example demonstrates how to use the mouse scroll wheel.
// It uses the new event-driven runtime to capture mouse events.
// ===================================================================

#include "../include/kontra.hpp"
#include <vector>
#include <string>

int main() {
    // --- 1. Create a scrollable list ---
    auto scrollable_list = std::make_shared<List>();
    for (int i = 1; i <= 50; ++i) {
        scrollable_list->add(std::make_shared<Text>("Item number " + std::to_string(i)));
    }
    scrollable_list->set_gap(1);

    // --- 2. Layout the screen ---
    auto border = std::make_shared<Border>(
        scrollable_list,
        BorderStyleBuilder().set_title("Use Mouse Wheel to Scroll").build()
    );
    border->set_padding(1);

    auto screen = std::make_shared<Screen>(border);

    // --- 3. Run the application with the new Event Handler ---
    // The lambda now takes a constant reference to an InputEvent.
    kontra::run(screen, [&](const InputEvent& event) {

        // We use a switch on the event type to handle different inputs.
        switch (event.type) {
        case EventType::MOUSE_SCROLL_UP:
            scrollable_list->scroll_up();
            break;

        case EventType::MOUSE_SCROLL_DOWN:
            scrollable_list->scroll_down();
            break;

        case EventType::KEY_PRESS:
            // Exit on Ctrl+Q
            if (event.key == 17) {
                // To exit gracefully, we need a way to break the loop.
                // For now, we'll just call exit().
                exit(0);
            }
            break;

        default:
            // Ignore other events
            break;
        }
        });

    return 0;
}