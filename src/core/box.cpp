#include "core/box.hpp"
#include <algorithm>

#ifdef _WIN32
#undef min
#undef max
#endif

int Box::get_preferred_height(int width) const {
    if (fixed_height != -1) {
        return fixed_height;
    }
    if (child) {
        int child_width = (fixed_width != -1) ? fixed_width : width;
        return child->get_preferred_height(child_width);
    }
    return 1;
}

void Box::render(ScreenBuffer& buffer, int x, int y, int w, int h)  {
    Component::render(buffer, x, y, w, h);

    if (child) {
        int render_w = (fixed_width != -1) ? std::min(w, fixed_width) : w;
        int render_h = (fixed_height != -1) ? std::min(h, fixed_height) : h;

        child->render(buffer, x, y, render_w, render_h);
    }
}