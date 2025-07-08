#include "core/radio-group.hpp"

RadioGroup::RadioGroup(const std::vector<std::string>& options, int* target_idx, const RadioStyle& style)
    : target_index(target_idx), active_button_idx(0) {
    
    for (const auto& option_label : options) {
        radio_buttons.push_back(std::make_shared<Radio>(option_label, style));
    }
    
    for (const auto& btn : radio_buttons) {
        internal_list.add(btn);
    }

    if (!radio_buttons.empty()) {
        active_button_idx = *target_index;
    }
}
bool RadioGroup::handle_mouse_press(int x, int y) {
    for (size_t i = 0; i < radio_buttons.size(); ++i) {
        if (radio_buttons[i]->contains(x, y)) {
            active_button_idx = i;
            select_active();
            return true;
        }
    }
    return false;
}
void RadioGroup::focus_next() {
    if (radio_buttons.empty()) return;
    active_button_idx = (active_button_idx + 1) % radio_buttons.size();
}

void RadioGroup::focus_previous() {
    if (radio_buttons.empty()) return;
    active_button_idx = (active_button_idx - 1 + radio_buttons.size()) % radio_buttons.size();
}

void RadioGroup::select_active() {
    if (target_index) {
        *target_index = active_button_idx;
    }
}

int RadioGroup::get_preferred_height(int width) const {
    return internal_list.get_preferred_height(width);
}

void RadioGroup::render(ScreenBuffer& buffer, int x, int y, int w, int h) {
    Component::render(buffer, x, y, w, h);
    
    for (size_t i = 0; i < radio_buttons.size(); ++i) {
        radio_buttons[i]->set_active(i == active_button_idx);
        radio_buttons[i]->set_selected(i == *target_index);
    }

    internal_list.render(buffer, x, y, w, h);
}
