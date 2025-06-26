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

void Border::render(int x, int y, int w, int h) const {
    if (last_state.x == x && last_state.y == y && last_state.w == w && last_state.h == h && last_state.padding == padding) {
        if (!children.empty()) {
            int innerX = x + 1;
            int innerY = y + 1;
            int innerW = w - 2;
            int innerH = h - 2;
            if (innerW > 0 && innerH > 0) {
                children[0]->render(innerX + padding, innerY + padding, innerW - (2 * padding), innerH - (2 * padding));
            }
        }
        return;
    }
    clear_area(last_state.x, last_state.y, last_state.w, last_state.h);
    if (w >= 2 && h >= 2) {
        ansi::move_cursor(y, x);
        std::cout << ansi::tl << repeat(ansi::h, w - 2) << ansi::tr;
        for (int i = 1; i < h - 1; ++i) {
            ansi::move_cursor(y + i, x);
            std::cout << ansi::v;
            ansi::move_cursor(y + i, x + w - 1);
            std::cout << ansi::v;
        }
        ansi::move_cursor(y + h - 1, x);
        std::cout << ansi::bl << repeat(ansi::h, w - 2) << ansi::br;
    }

    if (!children.empty()) {
        int innerX = x + 1;
        int innerY = y + 1;
        int innerW = w - 2;
        int innerH = h - 2;
        if (innerW > 0 && innerH > 0) {
            children[0]->render(innerX + padding, innerY + padding, innerW - (2 * padding), innerH - (2 * padding));
        }
    }

    last_state = { x, y, w, h, padding };
}