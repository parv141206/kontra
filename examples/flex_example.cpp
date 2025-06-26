// ===================================================================
// KONTRA TUI: flex_example.cpp
//
// This example demonstrates the Flex layout container.
// A Flex container arranges its children either horizontally (Row) or
// vertically (Column). Its key feature is that it divides the available
// space equally among all its children. This is useful for creating
// side-by-side panels or evenly spaced sections.
// ===================================================================
#include "../include/kontra.hpp"
int main() {
	// --- 1. Create Components to Arrange ---
	// We'll create several Text components with background colors to
	// clearly visualize how the Flex container allocates space.
	auto text1 = std::make_shared<Text>("Panel 1", TextStyle("", ansi::BG_RED));
	auto text2 = std::make_shared<Text>("Panel 2", TextStyle("", ansi::BG_GREEN));
	auto text3 = std::make_shared<Text>("Panel 3", TextStyle("", ansi::BG_BLUE));

	// --- 2. Create a Horizontal Flex Layout (Row) ---
	// This Flex container will arrange its children from left to right.
	// It will divide the total screen width by 3 for these children.
	auto flex_row = std::make_shared<Flex>(
		FlexDirection::Row,
		text1,
		text2,
		text3
	);
	// A gap adds empty columns between the children.
	flex_row->set_gap(5);

	// --- 3. Create a Vertical Flex Layout (Column) ---
	// This Flex container will arrange its children from top to bottom.
	// We reuse the same text components for this demonstration.
	auto flex_column = std::make_shared<Flex>(
		FlexDirection::Column,
		text1,
		text2,
		text3
	);
	flex_column->set_gap(1);

	// --- 4. Combine Both Examples on One Screen ---
	// We can nest layouts. Here, a vertical Flex container holds our
	// row example and our column example, stacking them.
	auto main_layout = std::make_shared<Flex>(
		FlexDirection::Column,
		flex_row,
		flex_column
	);

	auto screen = std::make_shared<Screen>(main_layout);

	// --- 5. Run the Application ---
	kontra::run(screen, [&](char ch) {
		if (ch == 17) { // Exit on Ctrl+Q
			exit(0);
		}
		});

	return 0;
}
