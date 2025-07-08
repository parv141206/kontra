#include "core/button.hpp"

void Button::set_active(bool is_active)
{
	active = is_active;
}

bool Button::is_active() const
{
	return active;
}

void Button::click()
{
	if (on_click_callback)
		on_click_callback();
}

int Button::get_preferred_height(int width) const
{
	Text temp_renderer(label_provider(), TextStyle());
	return temp_renderer.get_preferred_height(width);
}

void Button::render(ScreenBuffer &buffer, int x, int y, int w, int h)
{
	Component::render(buffer, x, y, w, h);
    
    const TextStyle& current_text_style = is_active() ? style.active_style : style.inactive_style;

	Text text_renderer(label_provider(), current_text_style);

	text_renderer.render(buffer, x, y, w, h);
}
