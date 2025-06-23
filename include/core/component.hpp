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
protected:
	mutable bool dirty = true;
public:

	/**
	 * Marks the component as dirty, indicating that it needs to be redrawn.
	 */
	void mark_dirty() const { dirty = true; }

	/**
	 * Clears the dirty flag, indicating that the component does not need to be redrawn.
	 */
	void clear_dirty() const { dirty = false; }

	/**
	 * Checks if the component is marked as dirty.
	 * \return true if the component is dirty, false otherwise.
	 */
	bool is_dirty() const { return dirty; }


	/**
	 * \brief Renders the component at the specified position and size.
	 * \param x The x-coordinate of the component's position.
	 * \param y The y-coordinate of the component's position.
	 * \param w The width of the component.
	 * \param h The height of the component.
	 */
	virtual void render(int x, int y, int w, int h) const = 0;

	/**
	 * \brief Returns the preferred height of the component for a given width.
	 * Used to prevent overflowing of content like text.
	 * \param width The width given to the component.
	 */
	virtual int get_preferred_height(int width) const { return 1; }

	virtual ~Component() = default;
};
