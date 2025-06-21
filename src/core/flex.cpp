#include "core/flex.hpp"
#include "core/ansi.hpp"

void Flex::add(std::shared_ptr<Component> comp) {
	children.push_back(std::move(comp));
}

Flex& Flex::set_gap(int g) {
	gap = g;
	return *this;
}

Flex& Flex::set_padding(int p) {
	padding = p;
	return *this;
}

void Flex::clear() {
	children.clear();
}

/**
 * @brief Renders the Flex container and its children within the specified dimensions.
 *
 * This function divides the available space (width and height) among the child elements
 * based on the Flex container's direction (Column or Row). It then calls the render
 * method of each child element to draw them in their respective positions.
 *
 * @param x The x-coordinate of the top-left corner of the container.
 * @param y The y-coordinate of the top-left corner of the container.
 * @param w The width of the container.
 * @param h The height of the container.
 *
 * @details
 * - If the direction is FlexDirection::Column, the height is divided equally among the children.
 * - If the direction is FlexDirection::Row, the width is divided equally among the children.
 * - The cursor is moved to the appropriate position before rendering each child.
 * - If there are no children, the function returns immediately without rendering.
 */
void Flex::render(int x, int y, int w, int h) const {
	auto [termWidth, termHeight] = ansi::get_terminal_size();
	int absWidth = (w * 100) / 100;
	int absHeight = (h * 100) / 100;

	int count = children.size();
	if (count == 0) return;

	if (direction == FlexDirection::Column) {
		int totalGap = gap * (count - 1);
		int availableHeight = absHeight - totalGap;
		int childHeight = availableHeight / count;
		int currentY = y;

		for (int i = 0; i < count; ++i) {
			children[i]->render(x, currentY, absWidth, childHeight);
			currentY += childHeight + gap;
		}
	}
	else if (direction == FlexDirection::Row) {
		int totalGap = gap * (count - 1);
		int availableWidth = absWidth - totalGap;
		int childWidth = availableWidth / count;
		int currentX = x;

		for (int i = 0; i < count; ++i) {
			children[i]->render(currentX, y, childWidth, absHeight);
			currentX += childWidth + gap;
		}
	}
}

