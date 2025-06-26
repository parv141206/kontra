#include "core/border.hpp" 
#include "core/ansi.hpp"  
#include "core/utils.hpp"
#include <iostream>        
#include <string>          
#include <algorithm>
#include <memory>
#ifdef _WIN32
#undef min
#undef max
#endif

int Border::get_preferred_height(int width) const {
	int inner_width = width > 2 ? width - 2 - (2 * padding) : 0;
	int children_height = 0;
	for (const auto& child : children) {
		if (child) {
			children_height += child->get_preferred_height(inner_width);
		}
	}
	return children_height + 2 + (2 * padding);
}


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

void Border::render(ScreenBuffer& buffer, int x, int y, int w, int h) const {
	std::string border_style = ansi::RESET;

	if (w >= 2 && h >= 2) {
		buffer.set_cell(x, y, ansi::tl, border_style);
		buffer.set_cell(x + w - 1, y, ansi::tr, border_style);
		buffer.set_cell(x, y + h - 1, ansi::bl, border_style);
		buffer.set_cell(x + w - 1, y + h - 1, ansi::br, border_style);
		for (int j = 1; j < w - 1; ++j) {
			buffer.set_cell(x + j, y, ansi::h, border_style);
			buffer.set_cell(x + j, y + h - 1, ansi::h, border_style);
		}
		for (int i = 1; i < h - 1; ++i) {
			buffer.set_cell(x, y + i, ansi::v, border_style);
			buffer.set_cell(x + w - 1, y + i, ansi::v, border_style);
		}
	}

	if (!children.empty()) {
		int innerX = x + 1;
		int innerY = y + 1;
		int innerW = w - 2;
		int innerH = h - 2;
		if (innerW > 0 && innerH > 0) {
			children[0]->render(buffer, innerX + padding, innerY + padding, innerW - (2 * padding), innerH - (2 * padding));
		}
	}
}