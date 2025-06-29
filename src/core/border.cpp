#include "core/border.hpp" 
#include "core/ansi.hpp"  
#include "core/utils.hpp"
#include "core/screen_buffer.hpp"
#include <string>          
#include <algorithm>
#include <memory>

#ifdef _WIN32
#undef min
#undef max
#endif



void Border::set_child(std::shared_ptr<Component> child_component)
{
	child = std::move(child_component);
}

int Border::get_preferred_height(int width) const {
    int inner_width = width > 2 ? width - 2 - (2 * padding) : 0;
    int child_height = 0;
    if (child) {
        child_height = child->get_preferred_height(inner_width);
    }
    return child_height + 2 + (2 * padding);
}

Border& Border::set_padding(int p) {
    padding = p;
    return *this;
}

void Border::render(ScreenBuffer& buffer, int x, int y, int w, int h) const {
    std::string full_style = style.color + style.background_color;
    const auto& chars = style.characters;

    if (w < 2 || h < 2) return; 

    if (!style.background_color.empty()) {
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                buffer.set_cell(x + j, y + i, " ", full_style);
            }
        }
    }

    for (int i = 1; i < h - 1; ++i) {
        buffer.set_cell(x, y + i, chars.v, full_style);
        buffer.set_cell(x + w - 1, y + i, chars.v, full_style);
    }
    for (int j = 1; j < w - 1; ++j) {
        buffer.set_cell(x + j, y + h - 1, chars.h, full_style);
    }

    if (style.title.empty() || style.title.length() > w - 4) {
        for (int j = 1; j < w - 1; ++j) buffer.set_cell(x + j, y, chars.h, full_style);
    }
    else {
        std::string display_title = " " + style.title + " ";
        int title_len = display_title.length();
        int title_start_col = (style.title_alignment == TitleAlignment::Left) ? 2 : ((style.title_alignment == TitleAlignment::Right) ? w - title_len - 2 : (w - title_len) / 2);

        for (int j = 1; j < title_start_col; ++j) buffer.set_cell(x + j, y, chars.h, full_style);
        for (int j = 0; j < title_len; ++j) buffer.set_cell(x + title_start_col + j, y, std::string(1, display_title[j]), full_style);
        for (int j = title_start_col + title_len; j < w - 1; ++j) buffer.set_cell(x + j, y, chars.h, full_style);
    }

    buffer.set_cell(x, y, chars.tl, full_style);
    buffer.set_cell(x + w - 1, y, chars.tr, full_style);
    buffer.set_cell(x, y + h - 1, chars.bl, full_style);
    buffer.set_cell(x + w - 1, y + h - 1, chars.br, full_style);

    if (child) {
        int innerX = x + 1;
        int innerY = y + 1;
        int innerW = w - 2;
        int innerH = h - 2;
        if (innerW > 0 && innerH > 0) {
            child->render(buffer, innerX + padding, innerY + padding, innerW - (2 * padding), innerH - (2 * padding));
        }
    }
}