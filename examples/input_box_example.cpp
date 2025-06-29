// ===================================================================
// KONTRA TUI: input_box_example.cpp
//
// This example demonstrates the `InputBox` component.
// It shows how to:
// - Create an input box.
// - Set it as "active" to receive keyboard input.
// - Use `handle_input()` to process keystrokes.
// - Use `get_text()` to retrieve its content.
// - Create a "mirror" Text component for real-time feedback.
// ===================================================================

#include "../include/kontra.hpp"

int main() {
    // --- 1. Component Initialization ---
    // Create the InputBox. It's crucial to set it as active.
    auto input_box = std::make_shared<InputBox>();
    
	input_box->set_label("Type something: ");

    input_box->set_active(true);

	// If you want to enable "text wrapping", you can do so:
	input_box->set_wrap_enabled(true);

    // Create a Text component that will "mirror" the input box's content.
    // The lambda `[&](){ ... }` makes this happen automatically. Every time
    // the UI is rendered, the Text component will call `get_text()` and
    // display the latest content.
    auto mirror_text = std::make_shared<Text>(
        [&]() { return "InputBox contains: " + input_box->get_text(); }
    );

    // --- 2. Layout ---
    // We'll stack the mirror text and the input box vertically using a List.
    auto layout = std::make_shared<List>(
        mirror_text,
        input_box
    );
    layout->set_gap(2);

    auto screen = std::make_shared<Screen>(
        std::make_shared<Border>(layout)
    );

    // --- 3. Event Loop ---
    // The logic is simple: pass every character (that isn't the exit key)
    // directly to the input box's `handle_input` method.
    kontra::run(screen, [&](char ch) {
        if (ch == 17) { // Exit on Ctrl+Q
            exit(0);
        }

        // The InputBox component knows how to handle backspace, arrows,
        // and printable characters internally.
        input_box->handle_input(ch);
        });

    return 0;
}