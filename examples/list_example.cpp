// ===================================================================
// KONTRA TUI: list_example.cpp
//
// This example demonstrates the `List` layout container.
// A List arranges its children vertically, similar to Flex(Column).
// However, the key difference is that a List respects each child's
// preferred height (`get_preferred_height()`). It does not stretch
// children to fill space. This is ideal for lists where items have
// varying heights, like a list of comments or a menu.
// ===================================================================

#include "../include/kontra.hpp"

int main() {
    // --- 1. Create Components with Different Heights ---
    // We'll create Text components of varying line counts to show
    // how List respects their individual height requirements.
    auto item1 = std::make_shared<Text>("This is a single-line item.");
    auto item2 = std::make_shared<Text>("This is a\nmulti-line item\nthat takes up more space.");
    auto item3 = std::make_shared<Text>("This is another single-line item.");

    // Lists can contain any type of component. Let's add an InputBox.
    auto input_item = std::make_shared<InputBox>();
    input_item->set_text("Lists can contain other components too!");

    // --- 2. Create the List Layout ---
    // We add all our items to the List. It will stack them vertically.
    auto main_list = std::make_shared<List>(
        item1,
        item2,
        item3,
        input_item
    );

    // The gap adds a blank line between each item in the list.
    main_list->set_gap(1);

    // --- 3. Create the Screen and Run ---
    auto screen = std::make_shared<Screen>(
        std::make_shared<Border>(main_list)
    );

    kontra::run(screen, [&](const InputEvent& event) {
        switch (event.type) {
        case EventType::KEY_PRESS:
            input_item->handle_input(event.key);
            break;
        case EventType::MOUSE_SCROLL_UP:
            main_list->scroll_up();
            break;
        case EventType::MOUSE_SCROLL_DOWN:
            main_list->scroll_down();
            break;
        default:
            break;
        }
        });

    return 0;
}