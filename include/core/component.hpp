/*****************************************************************//**
 * \file   component.hpp
 * \brief  This file defines the Component interface for GUI elements.
 * The component can be inherited to create specific GUI components. 
 * Each component must implement the render method to draw itself.
 * 
 * \author parv141206
 * \date   June 2025
 *********************************************************************/
#pragma once
#include <iostream>

class Component
{
public:
    /**
     * \brief Renders the component at the specified position and size.
     * \param x The x-coordinate of the component's position.
     * \param y The y-coordinate of the component's position.
     * \param w The width of the component.
     * \param h The height of the component.
	 */ 
    virtual void render(int x, int y, int w, int h) const = 0;
    virtual ~Component() = default;
};
