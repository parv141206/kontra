// ===================================================================
// KONTRA TUI: main.cpp
//
// First of all, thank you for using KONTRA TUI!
// 
// Its great to have you here!
// 
// This file provides a simple "Hello, World!" example to explain the
// basic flow and usage of the Kontra TUI library.
// 
// ===================================================================
#include "../include/kontra.hpp" // The main header for the library.
#include <memory>                // For std::make_shared

int main() {
    // It's good practice to clear the terminal screen before starting
    // the TUI application to ensure a clean slate.
    ansi::clear_screen();

    // ===================================================================
    // THE KONTRA TUI APPLICATION FLOW
    // Building an app follows a simple, logical flow:
    // 1. Create your content (like Text or InputBox components).
    // 2. Arrange your content in Layouts (like List, Flex, or Border).
    // 3. Place your top-level layout into a root Screen component.
    // 4. Pass the Screen to `kontra::run()` to start the application.
    // ===================================================================


    // --- Step 1: Create the Content ---
    // The most basic component is `Text`. We create it using `std::make_shared`
    // because all components are managed by smart pointers.
    // The `TextStyle` is optional but allows for easy styling.
    auto hello_text = std::make_shared<Text>(
        "Hello, may the force be with you!",
        TextStyle(ansi::FG_YELLOW, "", true) // Yellow, bold text
    );


    // --- Step 2: Create the Layout ---
    // We want to put our text inside a box. The `Border` component is a
    // container that does exactly this. It takes another component as
    // its child in its constructor.
    auto bordered_text = std::make_shared<Border>(hello_text);

    // We can chain methods to configure our layout. `set_padding` adds
    // empty space between the border lines and the content inside it.
    bordered_text->set_padding(2);


    // --- Step 3: Create the Screen ---
    // The `Screen` component is the root of your entire UI. It's the canvas
    // that everything else is rendered onto. It takes your main layout
    // component as its child.
    auto screen = std::make_shared<Screen>(bordered_text);


    // --- Step 4: Run the Application ---
    // `kontra::run` takes control of the terminal, starts the main event loop,
    // and handles drawing the screen and listening for keyboard input.

    // The second argument is a C++ lambda function. This function is your
    // "event handler" - it gets called automatically every time a key is pressed.
    // The character of the key that was pressed is passed in as `ch`.
    // UPDATED: The lambda now takes an InputEvent.
    // The main loop already handles Ctrl+Q for exiting.
    kontra::run(screen, [&](const InputEvent& event) {
        // This example is static and requires no input handling.
        });


    return 0;
}