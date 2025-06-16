#include "core/text.hpp"

/*
* @brief Renders the text at the specified position and size.
* 
* @param x The x-coordinate where rendering starts.
* @param y The y-coordinate where rendering starts.
* @param w The width of the area to render.
* @param h The height of the area to render.
* 
*/
void Text::render(int x, int y, int w, int h) const
{
	if (text.empty()) return;
	std::cout << text;
}
