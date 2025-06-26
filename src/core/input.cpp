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


void Input::render(int x, int y, int w, int h) const {
    bool frame_changed = !(
        last_state.x == x && last_state.y == y && last_state.w == w && last_state.h == h &&
        last_state.child_count == children.size() && last_state.gap == gap && last_state.padding == padding
        );

    if (frame_changed) {
        clear_area(last_state.x, last_state.y, last_state.w, last_state.h);
    }

    int currentY = y + padding;
    int inner_w = w - (2 * padding);
    for (const auto& child : children) {
        int child_h = child->get_preferred_height(inner_w);
        if (currentY + child_h > y + h) break;
        child->render(x + padding, currentY, inner_w, child_h);
        currentY += child_h + gap;
    }

    if (frame_changed) {
        last_state = { x, y, w, h, children.size(), gap, padding };
    }
}