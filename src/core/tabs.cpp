#include "../include/core/tabs.hpp"

void Tabs::change_tab(int tab_idx)
{
    if(tab_idx >= 0 && tab_idx < tabs.size()){
        current_tab_idx=tab_idx;
    }
}

void Tabs::next_tab()
{
    if(current_tab_idx+1 < tabs.size()){
        current_tab_idx++;
    }
}

void Tabs::previous_tab()
{
    if(current_tab_idx-1 > 0){
        current_tab_idx--;
    }
}

void Tabs::handle_mouse_input(int mouse_x, int mouse_y) {
    for (size_t i = 0; i < tabs.size(); ++i) {
        if (tabs[i]->contains(mouse_x, mouse_y)) {
            change_tab(i);
            return;
        }
    }
}



void Tab::render(ScreenBuffer &buffer, int x, int y, int w, int h)
{
    Component::render(buffer, x, y, w, h);
    child->render(buffer, x, y , w , h);

}

void Tabs::render(ScreenBuffer& buffer, int x, int y, int w, int h) {
    Component::render(buffer, x, y, w, h);
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;

    const std::string full_bg = style.bg;
    const auto& chars = style.border_chars;

    if (w < 2 || h < 2) return;

    // background
    if (!style.bg.empty()) {
        for (int i = 0; i < h; ++i)
            for (int j = 0; j < w; ++j)
                buffer.set_cell(x + j, y + i, " ", full_bg);
    }

    // vertical edges
    for (int i = 1; i < h - 1; ++i) {
        buffer.set_cell(x, y + i, chars.v, style.default_fg + full_bg);
        buffer.set_cell(x + w - 1, y + i, chars.v, style.default_fg + full_bg);
    }

    // horizontal bottom
    for (int j = 1; j < w - 1; ++j)
        buffer.set_cell(x + j, y + h - 1, chars.h, style.default_fg + full_bg);

    // corners
    buffer.set_cell(x, y, chars.tl, style.default_fg + full_bg);
    buffer.set_cell(x + w - 1, y, chars.tr, style.default_fg + full_bg);
    buffer.set_cell(x, y + h - 1, chars.bl, style.default_fg + full_bg);
    buffer.set_cell(x + w - 1, y + h - 1, chars.br, style.default_fg + full_bg);

    // Labels 
    int col = x + 1;

    if (col < x + w - 1)
        buffer.set_cell(col++, y, chars.v, style.default_fg + full_bg);

    for (size_t i = 0; i < tabs.size(); ++i) {
        std::string label = " " + tabs[i]->get_label() + " ";
        std::string tab_style = (i == current_tab_idx)
            ? style.active_fg + full_bg
            : style.default_fg + full_bg;

        int label_start = col;

        for (char ch : label) {
            if (col < x + w - 1)
                buffer.set_cell(col++, y, std::string(1, ch), tab_style);
        }

        int label_end = col;

        if (col < x + w - 1)
            buffer.set_cell(col++, y, chars.v, style.default_fg + full_bg);

        tabs[i]->last_x = label_start;
        tabs[i]->last_y = y;
        tabs[i]->last_w = label_end - label_start;
        tabs[i]->last_h = 1;
    }

    for (; col < x + w - 1; ++col)
        buffer.set_cell(col, y, chars.h, style.default_fg + full_bg);

    if (!tabs.empty()) {
        int innerX = x + 1;
        int innerY = y + 1;
        int innerW = w - 2;
        int innerH = h - 2;

        tabs[current_tab_idx]->render(buffer, innerX, innerY, innerW, innerH);
    }
}
