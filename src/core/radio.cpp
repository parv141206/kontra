#include "core/radio.hpp"

int Radio::get_preferred_height(int width) const {
    int label_width = (width > 4) ? width - 4 : 0;
    Text temp_renderer(label, TextStyle());
    return temp_renderer.get_preferred_height(label_width);
}

void Radio::render(ScreenBuffer& buffer, int x, int y, int w, int h) {
    Component::render(buffer, x, y, w, h);

    const TextStyle& current_style = is_active ? style.active : style.normal;
    std::string marker = is_selected ? "(o) " : "( ) ";
    std::string full_text = marker + label;

    Text text_renderer(full_text, current_style);
    text_renderer.render(buffer, x, y, w, h);
}
