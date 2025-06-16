#include "core/screen.hpp"
#include "core/ansi.hpp"

/*
* 
* @brief Renders the screen by clearing it and rendering all child components.
* 
* @param x The x-coordinate where rendering starts.
* @param y The y-coordinate where rendering starts.
* @param w The width of the area to render.
* @param h The height of the area to render.
* 
*/
void Screen::render(int x, int y, int w, int h) const {
	ansi::clear_screen();

	for (const auto& child : children) {
		child->render(x, y, w, h);
	}
}