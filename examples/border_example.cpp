// ===================================================================
// KONTRA TUI: border_example.cpp
//
// This example demonstrates the basic usage of the `Border` component.
// A Border acts as a simple container that draws a box around its
// single child component. It's useful for visually grouping elements.
// ===================================================================

#include "../include/kontra.hpp"

int main() {
	// --- 1. Define the Component to be Wrapped ---
	// We'll create a simple Text component that will go inside the border.
	auto inner_text = std::make_shared<Text>(
		"This text is inside a padded border.",
		TextStyle(ansi::FG_CYAN)
	);

	// Might as well add some styles!
	auto border_style = BorderStyleBuilder()
		.set_color(ansi::FG_GREEN)
		.set_background_color(ansi::BG_DEFAULT)
		.set_title("Success!")
		.set_title_alignment(TitleAlignment::Center)
		.set_characters(BorderPreset::DOUBLE)
		.build();
	
	// --- 2. Create the Border ---
	// The Border is initialized with the component it should contain.
	// We can then chain methods like `set_padding()` to configure it.
	auto bordered_component = std::make_shared<Border>(inner_text , border_style);

	// Padding adds empty cells between the border lines and the child's content.
	bordered_component->set_padding(2);

	// --- 3. Create the Screen ---
	// The Screen is the root component that holds our final layout.
	// For this simple example, the bordered component is the only thing on screen.
	auto screen = std::make_shared<Screen>(bordered_component);

	// --- 4. Run the Application ---
	// The event loop is minimal here. It just waits for the user to exit.
	// The UI is static and doesn't require any input handling.
	kontra::run(screen, [&](const InputEvent& event) {
		// Static example, no input needed. Exit is handled by runtime.
		});

	return 0;
}
