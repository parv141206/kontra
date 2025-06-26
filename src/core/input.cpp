#include "core/input.hpp"
#include "core/ansi.hpp"
#include <iostream>

int Input::get_preferred_height(int width) const {
	int absWidth = width > 2 * padding ? width - 2 * padding : 0;
	int total = 0;
	if (!children.empty()) {
		for (const auto& child : children) {
			total += child->get_preferred_height(absWidth);
		}
		total += gap * (children.size() - 1);
	}
	total += 2 * padding;
	return total;
}

void Input::add(std::shared_ptr<InputBox> inputBox) {
	children.push_back(std::move(inputBox));
}

void Input::clear() {

	children.clear();
}

Input& Input::set_gap(int g) {
	gap = g;
	return *this;
}

Input& Input::set_padding(int p) {
	padding = p;
	return *this;
}


void Input::render(ScreenBuffer& buffer, int x, int y, int w, int h) const {
	int currentY = y + padding;
	int inner_w = w - (2 * padding);
	for (const auto& child : children) {
		int child_h = child->get_preferred_height(inner_w);
		if (currentY + child_h > y + h) break;
		child->render(buffer, x + padding, currentY, inner_w, child_h);
		currentY += child_h + gap;
	}
}