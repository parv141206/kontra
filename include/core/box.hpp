/*****************************************************************//**
 * \file   box.hpp
 * \brief  A simple container to size components to a fixed size.
 * 
 * \author parv141206
 * \date   June 2025
 *********************************************************************/
#pragma once
#include "component.hpp"
#include <memory>

/**
 * @brief A box to render a child in constrained dimensions (fixed height and width).
 * 
 * Width and height can be set using `set_width` and `set_height` methods.
 * 
 * Set width and height to -1 to make it unconstrained.
 * 
 * Example
 * ```cpp
 * auto boxed_layout = std::make_shared<Box>(child);
 * boxed_layout->set_height(10);
 * boxed_layout->set_width(10);
 * 
 * // or
 * 
 * chain(
 *     std::make_shared<Box>(child),
 *     [](Box& b) {
 *         b.set_height(10);
 *         b.set_width(5);
 *     }
 * );
 * ```
 */
class Box : public Component {
    std::shared_ptr<Component> child;
    int fixed_width = -1;  // -1 means no constraint
    int fixed_height = -1; // -1 means no constraint

public:
    explicit Box(std::shared_ptr<Component> child_component) : child(child_component) {}

    /**
	 * \brief Sets the width of the box and its child component.
	 * \param w The fixed width to set. 
     */
    Box& set_width(int w) {
        fixed_width = w;
        return *this;
    }

    /**
     * \brief Sets the height of the box and its child component.
     * \param w The fixed height to set.
     */
    Box& set_height(int h) {
        fixed_height = h;
        return *this;
    }

    int get_preferred_height(int width) const override;

    /**
     * @brief Renders the box at the specified position and size.
     * @param x The x-coordinate of the input box's position.
     * @param y The y-coordinate of the input box's position.
     * @param w The width of the input box.
     * @param h The height of the input box.
     */
    void render(ScreenBuffer& buffer, int x, int y, int w, int h)  override;
};
