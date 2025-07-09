// ===================================================================
// KONTRA TUI Example: box_example.cpp
//
// This example demonstrates the use of the `Box` component, which allows
// you to constrain a child component's dimensions (width and height).
//
// The `Box` is often used for layout control — to give structure to text,
// buttons, or other components inside lists or borders.
//
// In this example, we wrap a `Text` component with a `Box`, constrain its
// size, and then wrap that inside a `Border` with padding and a title.
// ===================================================================

#include <memory>
#include "../include/kontra.hpp"

int main() {
    // Clear the terminal screen before rendering.
    ansi::clear_screen();

    // --- 1. Create the Core Text Component ---
    // This is the message that will be wrapped in a Box and then bordered.
    auto hello_text = std::make_shared<Text>(
        "Hello, may the force be with you!",
        TextStyle(ansi::FG_YELLOW, "", true) // bold yellow text
    );

    // --- 2. Wrap Text in a Box ---
    // The Box constrains the dimensions of its child. You can set width/height.
    // Note: You can also do this manually as shown below:
    //
    //   auto boxed_layout = std::make_shared<Box>(hello_text);
    //   boxed_layout->set_height(10);
    //   boxed_layout->set_width(10);
    //
    // We'll use the `chain()` utility to configure it inline:
    auto boxed_text = chain(
        std::make_shared<Box>(hello_text),
        [](Box& b) {
            b.set_height(10); // fixed height
            b.set_width(5);   // fixed width
        }
    );

    // --- 3. Wrap the Box in a Border ---
    // This provides a styled visual container around the boxed content.
    auto bordered_text = std::make_shared<Border>(
        boxed_text,
        BorderStyleBuilder()
            .set_title("Hello World")
            .build()
    );

    // Add padding between the border and the inner Box content.
    bordered_text->set_padding(2);

    // --- 4. Create and Run the Screen ---
    // The Screen is the root component of the UI tree.
    auto screen = std::make_shared<Screen>(bordered_text);

    kontra::run(screen, [&](const InputEvent& event) {
        // No input handling needed in this static example.
    });

    return 0;
}
