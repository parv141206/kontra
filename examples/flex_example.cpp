// ===================================================================
// KONTRA TUI: flex_example.cpp
//
// This example demonstrates the `Flex` layout container, correcting a
// common layout issue by using Flex as the top-level container.
// ===================================================================

#include "../include/kontra.hpp"

int main() {
    // --- 1. Create Components to Arrange ---
    auto panel1 = std::make_shared<Text>("Panel 1", TextStyle(ansi::FG_RED));
    auto panel2 = std::make_shared<Text>("Panel 2", TextStyle(ansi::FG_GREEN));
    auto panel3 = std::make_shared<Text>("Panel 3", TextStyle(ansi::FG_BLUE));

    // --- 2. Create the Horizontal (Row) Example ---
    auto flex_row = std::make_shared<Flex>(FlexDirection::Row, panel1, panel2, panel3);
    flex_row->set_gap(5);

    auto bordered_row_example = std::make_shared<Border>(
        flex_row,
        BorderStyleBuilder().set_title("FlexDirection::Row").set_color(ansi::FG_CYAN).build()
    );
    bordered_row_example->set_padding(1);

    // --- 3. Create the Vertical (Column) Example ---
    // NOTE: To avoid bugs with reusing components in multiple parents,
    // we create new instances for the second example.
    auto panel4 = std::make_shared<Text>("Panel 1", TextStyle(ansi::FG_RED));
    auto panel5 = std::make_shared<Text>("Panel 2", TextStyle(ansi::FG_GREEN));
    auto panel6 = std::make_shared<Text>("Panel 3", TextStyle(ansi::FG_BLUE));

    auto flex_column = std::make_shared<Flex>(FlexDirection::Column, panel4, panel5, panel6);
    flex_column->set_gap(1);

    auto bordered_column_example = std::make_shared<Border>(
        flex_column,
        BorderStyleBuilder().set_title("FlexDirection::Column").set_color(ansi::FG_YELLOW).build()
    );
    bordered_column_example->set_padding(1);

    // --- 4. THE FIX: Use Flex as the Main Layout ---
    // By using a Flex(Column) at the top level, we divide the entire screen
    // height between our two bordered examples, giving them space to "flex".
    auto main_layout = std::make_shared<Flex>(
        FlexDirection::Column,
        bordered_row_example,
        bordered_column_example
    );

    auto screen = std::make_shared<Screen>(main_layout);

    // --- 5. Run the Application ---
    kontra::run(screen, [&](char ch) {
        if (ch == 17) {
            exit(0);
        }
        });

    return 0;
}