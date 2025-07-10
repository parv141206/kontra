/*****************************************************************//**
 * \file   component.hpp
 * \brief  The base class for all components in the terminal UI.
 *********************************************************************/
#pragma once
#include <iostream>
#include "core/screen_buffer.hpp"

class Component
{
public:
    int last_x = -1, last_y = -1, last_w = -1, last_h = -1;
    virtual ~Component() = default;

    /**
     * Renders the component. The component itself will determine if a redraw
     * is necessary by comparing the new state (x,y,w,h, content) to its
     * last rendered state.
     */
    virtual void render(ScreenBuffer& buffer, int x, int y, int w, int h) {
        this->last_x = x;
        this->last_y = y;
        this->last_w = w;
        this->last_h = h;
    }

    /**
	 * \brief Checks if the component contains the given mouse coordinates, for handling mouse events.
	 * \param mouse_x The x-coordinate of the mouse event.
	 * \param mouse_y The y-coordinate of the mouse event.
     */
    bool contains(int mouse_x, int mouse_y) const {
        if (last_x == -1) return false; 

        int check_x = mouse_x - 1;
        int check_y = mouse_y - 1;

        return (check_x >= last_x && check_x < last_x + last_w &&
                check_y >= last_y && check_y < last_y + last_h);
    }

    /**
     * Returns the preferred height of the component. This is used to determine
     * how much space the component would like to occupy in a layout.
	 */
    virtual int get_preferred_height(int width) const { return 1; }

protected:
    /**
     * Helper function to clear a rectangular area of the terminal.
     * Every component will use this to erase its old self.
     */
    void clear_area(ScreenBuffer& buffer, int x, int y, int w, int h) const {
        if (w <= 0 || h <= 0) return;
        for (int i = 0; i < h; ++i) {
            std::cout << "\033[" << y + i << ";" << x << "H";
            for (int j = 0; j < w; ++j) {
                std::cout << ' ';
            }
        }
    }
};
