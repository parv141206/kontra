#include "core/border.hpp" 
#include "core/ansi.hpp"  
#include "core/utils.hpp"
#include <iostream>        
#include <string>          
#include <algorithm>
#include <memory>

void Border::add_component(const std::shared_ptr<Component>& comp) {
	children.push_back(comp);
}

void Border::add_component(std::shared_ptr<Component>&& comp) {
	children.push_back(std::move(comp));
}

Border& Border::set_padding(int p) {
	padding = p;
	return *this;
}

void Border::render(int x, int y, int w, int h) const {

	// Dirty check
	bool any_dirty = is_dirty();
	for (const auto& child : children) {
		if (child->is_dirty()) {
			any_dirty = true;
			break;
		}
	}
	if (!any_dirty) return;

	// I know following doesnt really make sense, for now it works , so it works :)
	auto [termWidth, termHeight] = ansi::get_terminal_size();
	int absWidth = (w * 100) / 100;
	int absHeight = (h * 100) / 100;

	if (absWidth < 2 || absHeight < 2) {
		int count = children.size();
		if (count > 0) {
			int childHeight = absHeight / count;
			for (int i = 0; i < count; ++i) {
				children[i]->render(x, y + i * childHeight, absWidth, childHeight);
			}
		}
		return;
	}

	ansi::move_cursor(y, x);
	std::cout << ansi::tl << repeat(ansi::h, absWidth - 2) << ansi::tr;

	for (int i = 1; i < absHeight - 1; ++i) {
		ansi::move_cursor(y + i, x);
		std::cout << ansi::v; 
		ansi::move_cursor(y + i, x + absWidth - 1);
		std::cout << ansi::v; 
	}

	ansi::move_cursor(y + absHeight - 1, x);
	std::cout << ansi::bl << repeat(ansi::h, absWidth - 2) << ansi::br;


	int innerX = x + 1;
	int innerY = y + 1;
	int innerW = absWidth - 2;
	int innerH = absHeight - 2;

	if (innerW <= 0 || innerH <= 0) return;

	int count = children.size();
	if (count == 0) return;

	int childHeight = innerH / count;
	int currentChildY = innerY;

	for (int i = 0; i < count; ++i) {
		children[i]->render(innerX + padding, currentChildY + padding, innerW - padding, childHeight - padding);
		currentChildY += childHeight;
	}
	clear_dirty();
	//for (const auto& child : children) child->clear_dirty();
}