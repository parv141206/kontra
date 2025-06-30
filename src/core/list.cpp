#include "core/list.hpp"
#include "core/ansi.hpp"
#include <iostream>
#include <numeric>
#include <algorithm>

#ifdef _WIN32
#undef min
#undef max
#endif

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

List& List::set_scrollbar_enabled(bool enabled) {
    scrollbar_enabled = enabled;
    return *this;
}

void List::clear() {
    children.clear();
}

void List::scroll_up(int amount) {
    scroll_offset = std::max(0, scroll_offset - amount);
}

void List::scroll_down(int amount) {
    scroll_offset += amount; // Clamping is handled in render()
}

int List::get_preferred_height(int width) const {
    int absWidth = width > 2 * padding ? width - 2 * padding : 0;
    if (scrollbar_enabled) absWidth--;

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

void List::render(ScreenBuffer& buffer, int x, int y, int w, int h) {
    Component::render(buffer, x, y, w, h);
    if (w <= 0 || h <= 0) return;

    int innerX = x + padding;
    int innerY = y + padding;
    int innerW = w - (2 * padding);
    int innerH = h - (2 * padding);

    int scrollbar_width = (scrollbar_enabled) ? 1 : 0;
    int content_w = innerW - scrollbar_width;

    if (content_w <= 0 || innerH <= 0) return;

    int total_content_height = 0;
    if (!children.empty()) {
        for (const auto& child : children) {
            total_content_height += child->get_preferred_height(content_w);
        }
        total_content_height += gap * (children.size() - 1);
    }

    bool is_scrollable = total_content_height > innerH;
    int max_scroll = 0;
    if (is_scrollable) {
        max_scroll = total_content_height - innerH;
        const_cast<List*>(this)->scroll_offset = std::min(scroll_offset, max_scroll);
        const_cast<List*>(this)->scroll_offset = std::max(0, scroll_offset);
    }
    else {
        const_cast<List*>(this)->scroll_offset = 0;
    }

    int currentY = innerY - scroll_offset;
    for (const auto& child : children) {
        int child_h = child->get_preferred_height(content_w);
        if (currentY + child_h > y && currentY < y + h) {
            child->render(buffer, innerX, currentY, content_w, child_h);
        }
        currentY += child_h + gap;
        if (currentY >= y + h + scroll_offset) break;
    }

    if (scrollbar_enabled && is_scrollable) {
        int scrollbarX = innerX + content_w;
        std::string track_style = ansi::RESET;
        std::string thumb_style = ansi::INVERSE;

        for (int i = 0; i < innerH; ++i) {
            buffer.set_cell(scrollbarX, innerY + i, u8"│", track_style);
        }

        int thumb_size = std::max(1, (innerH * innerH) / total_content_height);
        int thumb_pos = (scroll_offset * (innerH - thumb_size)) / max_scroll;

        for (int i = 0; i < thumb_size; ++i) {
            buffer.set_cell(scrollbarX, innerY + thumb_pos + i, u8"█", thumb_style);
        }
    }
}