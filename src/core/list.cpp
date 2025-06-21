#include "core/list.hpp"
#include "core/ansi.hpp"
#include <stdexcept>


void List::add(std::shared_ptr<Component> comp) {
	children.push_back(std::move(comp));
}


List& List::set_gap(int g) {
	gap = g;
	return *this;
}


List& List::set_padding(int p) {
	padding = p;
	return *this;
}

void List::clear() {
	children.clear();
}

/**
 * This is almost same as a Flex box but the thing is that this doesnt divide the space equally. stacks the children xD
 */
void List::render(int x, int y, int w, int h) const
{
	auto [termWidth, termHeight] = ansi::get_terminal_size();
	int absWidth = (w * 100) / 100;
	int absHeight = (h * 100) / 100;

	int count = children.size();
	if (count == 0) return;

	int childHeight = 0;
	int currentY = y;
	for (int i = 0; i < count; ++i) {
		if (currentY >= h) throw std::runtime_error("List height exceeded available space.");
		int childHeight = children[i]->get_preferred_height(absWidth);
		children[i]->render(x, currentY, absWidth, childHeight);
		currentY += childHeight + gap;
	}

}
