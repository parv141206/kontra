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

void Flex::render(int x, int y, int w, int h) const {
    bool frame_changed = !(
        last_state.x == x && last_state.y == y && last_state.w == w && last_state.h == h &&
        last_state.child_count == children.size() && last_state.gap == gap &&
        last_state.padding == padding && last_state.direction == direction
        );

    if (frame_changed) {
        clear_area(last_state.x, last_state.y, last_state.w, last_state.h);
    }

    int count = children.size();
    if (count > 0) {
        int innerX = x + padding;
        int innerY = y + padding;
        int innerW = w - (2 * padding);
        int innerH = h - (2 * padding);

        if (direction == FlexDirection::Column) {
            int totalGap = gap * (count - 1);
            int availableHeight = innerH - totalGap;
            int childHeight = availableHeight > 0 ? availableHeight / count : 0;
            int currentY = innerY;

            for (const auto& child : children) {
                if (currentY >= y + h) break;
                child->render(innerX, currentY, innerW, childHeight);
                currentY += childHeight + gap;
            }
        }
        else { // FlexDirection::Row
            int totalGap = gap * (count - 1);
            int availableWidth = innerW - totalGap;
            int childWidth = availableWidth > 0 ? availableWidth / count : 0;
            int currentX = innerX;

            for (const auto& child : children) {
                if (currentX >= x + w) break;
                child->render(currentX, innerY, childWidth, innerH);
                currentX += childWidth + gap;
            }
        }
    }

    if (frame_changed) {
        last_state = { x, y, w, h, children.size(), gap, padding, direction };
    }
}