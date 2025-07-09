// ===================================================================
// KONTRA TUI Example: border_example.cpp
//
// This example demonstrates how to use the `Border` component to visually
// wrap and style a child component (in this case, a `Text` element).
//
// The `Border` draws a styled box around a single child, with options for
// padding, border characters, color, title, and more. It's ideal for
// visually grouping components like form sections, messages, or lists.
// ===================================================================

#include "../include/kontra.hpp"

int main() {
    // --- 1. Define the Component to be Wrapped ---
    // We'll create a simple Text component that will go inside the border.
    auto inner_text = std::make_shared<Text>(
        "This text is inside a padded border.",
        TextStyle(ansi::FG_CYAN)
    );

    // --- 2. Build the Border Style ---
    // Here we configure the visual style for the border using BorderStyleBuilder.
    auto border_style = BorderStyleBuilder()
        .set_color(ansi::FG_GREEN)
        .set_background_color(ansi::BG_DEFAULT)
        .set_title("Success!")
        .set_title_alignment(TitleAlignment::Center)
        .set_characters(BorderPreset::DOUBLE)
        .build();

    // --- 3. Create the Border ---
    // The Border wraps the inner component and uses the style defined above.
    // Padding adds spacing between the content and the border box.
    auto bordered_component = std::make_shared<Border>(inner_text, border_style);
    bordered_component->set_padding(2);

    // --- 4. Create the Screen ---
    // The Screen is the top-level component passed to `kontra::run`.
    // It's the root of the UI tree. In this example, it just holds the border.
    auto screen = std::make_shared<Screen>(bordered_component);

    // --- 5. Run the Application ---
    // This is a static example. No input is handled here.
    kontra::run(screen, [&](const InputEvent& event) {
        // No interaction needed. Exit is handled internally (e.g., Ctrl+C).
    });

    return 0;
}
