/*****************************************************************//**
 * \file   component.hpp
 * \brief  The new, simplified component interface.
 *********************************************************************/
#pragma once
#include <iostream>

class Component
{
public:
    virtual ~Component() = default;

    /**
     * Renders the component. The component itself will determine if a redraw
     * is necessary by comparing the new state (x,y,w,h, content) to its
     * last rendered state.
     */
    virtual void render(int x, int y, int w, int h) const = 0;

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
    void clear_area(int x, int y, int w, int h) const {
        if (w <= 0 || h <= 0) return;
        for (int i = 0; i < h; ++i) {
            std::cout << "\033[" << y + i << ";" << x << "H";
            for (int j = 0; j < w; ++j) {
                std::cout << ' ';
            }
        }
    }
};