#include "core/checkbox.hpp"

void Checkbox::set_active(bool is_active) {
	active = is_active;
}

bool Checkbox::is_active() const {
	return active;
}

void Checkbox::toggle() {
	if (target_variable) {
		*target_variable = !(*target_variable);
	}
}

int Checkbox::get_preferred_height(int width) const {
    int label_width = (width > 4) ? width - 4 : 0;
    Text temp_renderer(label_provider(), TextStyle());
    return temp_renderer.get_preferred_height(label_width);
}

void Checkbox::render(ScreenBuffer& buffer, int x, int y, int w, int h) {
	Component::render(buffer, x, y, w, h);

	const TextStyle& current_style = active ? style.active : style.normal;

	std::string box_text = (target_variable && *target_variable) ? "[x] " : "[ ] ";
	
    std::string full_text = box_text + label_provider();
    
    Text text_renderer(full_text, current_style);
	text_renderer.render(buffer, x, y, w, h);
}
